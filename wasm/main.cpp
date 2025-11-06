#include "index.h"
#include "assert.h"

int main(int argc, char const *argv[])
{
    MainArea mainArea("main", sizeof(RecordData));
    IndexArea indexArea("index");

    indexArea.addRecord(100, 1);
    indexArea.addRecord(2, 2);
    indexArea.addRecord(50, 3);

    assert(indexArea.readRecord(50).value() == 3);
    assert(indexArea.readRecord(2) == 2);
    assert(indexArea.readRecord(100).value() == 1);
    return 0;
}
