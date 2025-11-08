//
// Created by ivan on 11/6/25.
//

#ifndef LAB4_PA_QT_MAIN_AREA_H
#define LAB4_PA_QT_MAIN_AREA_H

#include <cstddef>

struct MainRecord {
    int key;
    char name[50];
};

class MainArea {
public:
    MainArea(const char *filePath, size_t recordSize);

    const char *readByRecordNumber(int recordNumber);

    void writeRecord(const MainRecord &data);

    size_t getRecordCount() const;

    void deleteRecord(size_t recordNumber);

    void editRecord(size_t recordNumber, const MainRecord &data);

    const char *readAll() const;

    size_t fileSize();

    size_t recordSize();

    ~MainArea();

private
:
    int fd_;
    const char *filePath_;
    size_t recordSize_;
    size_t recordCount_;
    size_t fileSize_;
};


#endif //LAB4_PA_QT_MAIN_AREA_H
