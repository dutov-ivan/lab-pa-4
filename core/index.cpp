#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "index.h"

#include <vector>

#include "utils.h"

IndexArea::IndexArea(const char *filePath) : filePath_(filePath) {
    int fd = open(filePath_, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        throw std::runtime_error(
            "Failed to open index file '" + std::string(filePath_) + "': " + std::strerror(errno));
    }
    fd_ = fd;
    struct stat st{};
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        throw std::runtime_error("Failed to get info about file");
    }

    blockCount_ = (st.st_size + blockSize_ - 1) / blockSize_;
    if (blockCount_ == 0) {
        // Initializing first empty block
        char buffer[blockSize_] = {0};
        write(fd_, buffer, blockSize_);
        blockCount_ = 1;
    }
}

void IndexArea::addRecord(const int key, const int recordNumber) {
    // TODO: Add search among blocks
    off_t blockOffset = 0;
    if (lseek(fd_, blockOffset, SEEK_SET) == -1) {
        throw std::runtime_error(
            std::string("Failed to seek to block 0: ") + std::strerror(errno));
    }

    char blockBuffer[blockSize_];
    ssize_t bytesRead = read(fd_, blockBuffer, blockSize_);
    if (bytesRead == -1) {
        throw std::runtime_error(
            std::string("Failed to read block 0: ") + std::strerror(errno));
    }

    // Linear scan to find the first empty space.
    size_t slot = 0;
    while (slot < maxRecordCount_) {
        if (isEmptyRecord(blockBuffer + slot * recordSize_))
            break;
        ++slot;
    }

    if (slot == maxRecordCount_) {
        // TODO: Create a new block and rebalance
        throw std::runtime_error("New blocks are not implemented yet");
    }

    if (slot == 0) {
        // Just insert the record if the block is empty
        Record data{key, recordNumber};
        memcpy(blockBuffer, &data, sizeof(data));
        if (lseek(fd_, blockOffset, SEEK_SET) == -1) {
            throw std::runtime_error(
                std::string("Failed to seek to block 0 for writing: ") + std::strerror(errno));
        }
        if (write(fd_, blockBuffer, blockSize_) != blockSize_) {
            throw std::runtime_error("Failed to write record");
        }
        return;
    }

    size_t lastUsedRecord = slot - 1;

    size_t low = 0;
    size_t high = lastUsedRecord;

    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        int recordKey;
        memcpy(&recordKey, blockBuffer + mid * recordSize_, sizeof(int));

        if (recordKey == key) {
            throw std::runtime_error("Record with this primary key already exists");
        } else if (recordKey > key) {
            if (mid == 0)
                break; // avoid underflow
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    size_t insertAt = low;

    if (insertAt <= lastUsedRecord) {
        memmove(blockBuffer + (insertAt + 1) * recordSize_,
                blockBuffer + insertAt * recordSize_,
                (lastUsedRecord - insertAt + 1) * recordSize_);
    }

    Record newRec{key, recordNumber};
    memcpy(blockBuffer + insertAt * recordSize_, &newRec, recordSize_);

    if (lseek(fd_, blockOffset, SEEK_SET) == -1) {
        throw std::runtime_error(
            std::string("Failed to seek to block 0 for writing: ") + std::strerror(errno));
    }
    if (write(fd_, blockBuffer, blockSize_) != blockSize_) {
        throw std::runtime_error("Failed to write record");
    }
}

std::optional<int> IndexArea::readRecord(const int key) {
    // TODO: Add different blocks options
    std::vector<char> blockBuffer = readBlock(0);

    // Linear scan to find the first empty space.
    size_t slot = 0;
    while (slot < maxRecordCount_) {
        if (isEmptyRecord(blockBuffer.data() + slot * recordSize_))
            break;
        ++slot;
    }

    if (slot == 0) {
        return std::nullopt;
    }

    size_t lastUsedRecord = slot - 1;

    size_t low = 0;
    size_t high = lastUsedRecord;

    int recordKeyValue;
    size_t mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        std::memcpy(&recordKeyValue, blockBuffer.data() + mid * recordSize_, sizeof(int));

        if (recordKeyValue == key) {
            break;
        } else if (recordKeyValue > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (recordKeyValue != key) {
        return std::nullopt;
    }

    int recordNumber;
    std::memcpy(&recordNumber, blockBuffer.data() + mid * recordSize_ + sizeof(int), sizeof(int));

    return recordNumber;
}

bool IndexArea::isEmptyRecord(const char *start) {
    for (int i = 0; i < 4; i++) {
        if (start[i] != 0) {
            return false;
        }
    }
    return true;
}

size_t IndexArea::getBlockCount() const {
    return blockCount_;
}

std::vector<char> IndexArea::readBlock(const size_t blockNumber) const {
    if (blockNumber > blockCount_) {
        throw std::runtime_error("Block index can't be greater than overall number of blocks");
    }

    off_t blockOffset = static_cast<off_t>(blockNumber) * blockSize_;
    if (lseek(fd_, blockOffset, SEEK_SET) == -1) {
        throw std::runtime_error("Cannot move to the start of the block");
    }

    std::vector<char> blockBuffer(blockSize_);
    ssize_t bytesRead = read(fd_, blockBuffer.data(), blockSize_);
    if (bytesRead == -1) {
        throw std::runtime_error(
            std::string("Failed to read block 0: ") + std::strerror(errno));
    }

    return blockBuffer;
}

size_t IndexArea::editRecord(int oldKey, int newKey) {
    throw NotImplemented();
}

size_t IndexArea::deleteRecord(int key) {
    throw NotImplemented();
}

size_t IndexArea::blockSize() const {
    return blockSize_;
}

size_t IndexArea::recordSize() const {
    return recordSize_;
}

IndexArea::~IndexArea() {
    if (fd_ != -1) {
        close(fd_);
    }
}
