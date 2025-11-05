#include "index.h"

int main(int argc, char const *argv[])
{
    MainArea mainArea("main", sizeof(RecordData));
    IndexArea indexArea("index");

    indexArea.addRecord(100, 1);
    indexArea.addRecord(2, 2);
    indexArea.addRecord(50, 3);
    return 0;
}
