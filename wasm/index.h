#ifndef INDEX_H
#define INDEX_H

#include <cstddef>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

struct RecordData
{
    int key;
    char name[50];
};

class MainArea
{
public:
    MainArea(const char *filePath, size_t recordSize)
        : filePath_(filePath)
    {
        recordSize_ = recordSize;

        int fd = open(filePath_, O_RDWR | O_CREAT, 0644);
        if (fd == -1)
        {
            throw std::runtime_error(
                "Failed to open file '" + std::string(filePath_) + "': " + std::strerror(errno));
        }
        fd_ = fd;
    }

    const char *readByRecordNumber(int recordNumber)
    {
        size_t offset = recordNumber * recordSize_;
        if (lseek(fd_, offset, SEEK_SET) == -1)
        {
            throw std::runtime_error(
                "Failed to seek to record " + std::to_string(recordNumber) + ": " + std::strerror(errno));
        }

        char *buffer = new char[recordSize_];
        ssize_t bytesRead = read(fd_, buffer, recordSize_);
        if (bytesRead == -1)
        {
            delete[] buffer;
            throw std::runtime_error(
                "Failed to read record " + std::to_string(recordNumber) + ": " + std::strerror(errno));
        }
        if (static_cast<size_t>(bytesRead) < recordSize_)
        {
            delete[] buffer;
            throw std::runtime_error(
                "Incomplete read for record " + std::to_string(recordNumber));
        }

        return buffer; // Caller is responsible for deleting the buffer
    }

    void writeRecord(const RecordData &data)
    {
        if (sizeof(data) != recordSize_)
        {
            throw std::runtime_error("Cannot write record with size different from recordSize_");
        }

        if (lseek(fd_, 0, SEEK_END) == -1)
        {
            throw std::runtime_error(
                std::string("Failed to seek to the end of the main area file for writing: ") + std::strerror(errno));
        }
        write(fd_, &data, sizeof(data));
    }

    ~MainArea()
    {
        if (fd_ != -1)
        {
            close(fd_);
        }
    }

private:
    int fd_;
    const char *filePath_;
    size_t recordSize_;
};

struct Record
{
    int32_t key;
    int32_t recordNumber;
};

class IndexArea
{
public:
    explicit IndexArea(const char *filePath)
        : filePath_(filePath)
    {
        int fd = open(filePath_, O_RDWR | O_CREAT, 0644);
        if (fd == -1)
        {
            throw std::runtime_error(
                "Failed to open index file '" + std::string(filePath_) + "': " + std::strerror(errno));
        }
        fd_ = fd;
        // TODO: Read block count
        blockCount_ = 1;
    }

    void addRecord(int key, int recordNumber)
    {
        // TODO: Add search among blocks
        off_t blockOffset = 0;
        if (lseek(fd_, blockOffset, SEEK_SET) == -1)
        {
            throw std::runtime_error(
                std::string("Failed to seek to block 0: ") + std::strerror(errno));
        }

        char blockBuffer[blockSize_];
        ssize_t bytesRead = read(fd_, blockBuffer, blockSize_);
        if (bytesRead == -1)
        {
            throw std::runtime_error(
                std::string("Failed to read block 0: ") + std::strerror(errno));
        }

        // Linear scan to find the first empty space.
        size_t slot = 0;
        while (slot < maxRecordCount_)
        {
            if (isEmptyRecord(blockBuffer + slot * recordSize))
                break;
            ++slot;
        }

        if (slot == maxRecordCount_)
        {
            // TODO: Create a new block and rebalance
            throw std::runtime_error("New blocks are not implemented yet");
        }

        if (slot == 0)
        {
            // Just insert the record if the block is empty
            Record data{key, recordNumber};
            if (lseek(fd_, blockOffset, SEEK_SET) == -1)
            {
                throw std::runtime_error(
                    std::string("Failed to seek to block 0 for writing: ") + std::strerror(errno));
            }
            if (write(fd_, blockBuffer, blockSize_) != blockSize_)
            {
                throw std::runtime_error("Failed to write record");
            }
            return;
        }

        size_t lastUsedRecord = slot - 1;

        size_t low = 0;
        size_t high = lastUsedRecord;

        while (low <= high)
        {
            size_t mid = low + (high - low) / 2;
            if (isRecordKeyGreaterThan(blockBuffer + mid * recordSize, key))
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        size_t insertAt = low + 1;
        memmove(blockBuffer + (insertAt + 1) * recordSize,
                blockBuffer + insertAt * recordSize,
                (lastUsedRecord - insertAt) * recordSize);

        Record newRec{key, recordNumber};
        memcpy(blockBuffer + insertAt * recordSize, &newRec, recordSize);

        if (lseek(fd_, blockOffset, SEEK_SET) == -1)
        {
            throw std::runtime_error(
                std::string("Failed to seek to block 0 for writing: ") + std::strerror(errno));
        }
        if (write(fd_, blockBuffer, blockSize_) != blockSize_)
        {
            throw std::runtime_error("Failed to write record");
        }
    }

    bool isEmptyRecord(char *start)
    {
        for (int i = 0; i < 4; i++)
        {
            if (start[i] != 0)
            {
                return false;
            }
        }
        return true;
    }

    bool isRecordKeyGreaterThan(const char *recordKey, int key)
    {
        int recordKeyValue;
        std::memcpy(&recordKeyValue, recordKey, sizeof(int));
        return recordKeyValue > key;
    }

    ~IndexArea()
    {
        if (fd_ != -1)
        {
            close(fd_);
        }
    }

private:
    int fd_;
    const char *filePath_;
    const size_t blockSize_ = 128;
    size_t blockCount_;
    const double fillPercentage_ = 0.9;
    const size_t recordSize = sizeof(int) * 2; // key + recordNumber
    const size_t maxRecordCount_ = blockSize_ / recordSize;
};

#endif // INDEX_H