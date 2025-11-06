#ifndef INDEX_H
#define INDEX_H

#include <cstddef>
#include <optional>


struct Record {
    int32_t key;
    int32_t recordNumber;
};

class IndexArea {
public:
    explicit IndexArea(const char *filePath);

    void addRecord(int key, int recordNumber);

    std::optional<int> readRecord(int key);

    bool isEmptyRecord(char *start);

    ~IndexArea();

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
