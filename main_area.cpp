//
// Created by ivan on 11/6/25.
//

#include "main_area.h"
#include <fcntl.h>
#include <stdexcept>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>

MainArea::MainArea(const char *filePath, const size_t recordSize) : filePath_(filePath) {
    recordSize_ = recordSize;

    const int fd = open(filePath_, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        throw std::runtime_error(
            "Failed to open file '" + std::string(filePath_) + "': " + std::strerror(errno));
    }
    fd_ = fd;
    struct stat st{};
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        throw std::runtime_error("Failed to get info about file");
    }
    recordCount_ = (st.st_size + recordSize - 1) / recordSize_;
}

const char *MainArea::readByRecordNumber(int recordNumber) {
    if (recordNumber > recordCount_) {
        throw std::runtime_error("Cannot read such a record: doesn't exist");
    }
    size_t offset = recordNumber * recordSize_;
    if (lseek(fd_, offset, SEEK_SET) == -1) {
        throw std::runtime_error(
            "Failed to seek to record " + std::to_string(recordNumber) + ": " + std::strerror(errno));
    }

    const auto buffer = new char[recordSize_];
    const ssize_t bytesRead = read(fd_, buffer, recordSize_);
    if (bytesRead == -1) {
        delete[] buffer;
        throw std::runtime_error(
            "Failed to read record " + std::to_string(recordNumber) + ": " + std::strerror(errno));
    }
    if (static_cast<size_t>(bytesRead) < recordSize_) {
        delete[] buffer;
        throw std::runtime_error(
            "Incomplete read for record " + std::to_string(recordNumber));
    }

    return buffer; // Caller is responsible for deleting the buffer
}

void MainArea::writeRecord(const MainRecord &data) {
    if (sizeof(data) != recordSize_) {
        throw std::runtime_error("Cannot write record with size different from recordSize_");
    }

    if (lseek(fd_, 0, SEEK_END) == -1) {
        throw std::runtime_error(
            std::string("Failed to seek to the end of the main area file for writing: ") + std::strerror(errno));
    }
    write(fd_, &data, sizeof(data));
    recordCount_++;
}

size_t MainArea::getRecordCount() const {
    return recordCount_;
}

MainArea::~MainArea() {
    if (fd_ != -1) {
        close(fd_);
    }
}
