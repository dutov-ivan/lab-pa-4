#include "mainwindow.h"
#include "forms/ui_mainwindow.h"
#include <QMessageBox>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow), index("index"), mainArea("main", sizeof(MainRecord)) {
    ui->setupUi(this);
    // ui->recordKeyLineEdit->setValidator((new QIntValidator(0, 100000, this)));
    // ui->nameColumnLineEdit->setMaxLength(50);
    // Setting up TableViews
    indexModel = new RecordModel(this);
    ui->indexView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->indexView->setModel(indexModel);

    mainModel = new MainRecordModel(this);
    ui->mainView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mainView->setModel(mainModel);

    indexBlockPage = 0;
    std::vector<char> indexBlock = index.readBlock(indexBlockPage);
    syncDataToIndexView(indexBlock);

    const char *mainData = mainArea.readAll();
    syncDataToMainView(mainData);


    connect(ui->addRecordButton, &QPushButton::clicked, this, &MainWindow::onRecordAdd);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onRecordAdd() {
    // bool ok;
    // int recordKey = ui->recordKeyLineEdit->text().toInt(&ok);
    // if (!ok) {
    //     QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer");
    //     return;
    // }
    //
    // std::string name = ui->nameColumnLineEdit->text().toStdString();
    // const size_t nextRecordCount = mainArea.getRecordCount() + 1;
    // index.addRecord(recordKey, nextRecordCount);
    //
    // MainRecord record{};
    // record.key = recordKey;
    // std::memcpy(record.name, name.data(), std::min(name.size(), sizeof(record.name)));
    // mainArea.writeRecord(record);
}

void MainWindow::onIndexBlockChanged() {
}

void MainWindow::syncDataToIndexView(const std::vector<char> &block) {
    const size_t blockSize = index.blockSize();
    const size_t recordSize = index.recordSize();

    for (size_t i = 0; i < blockSize / recordSize; i++) {
        Record r{};
        memcpy(&r, block.data() + i * recordSize, recordSize);
        indexModel->addRecord(r);
    }
}

void MainWindow::syncDataToMainView(const char *block) {
    const size_t fileSize = mainArea.fileSize();
    const size_t recordSize = mainArea.recordSize();

    for (size_t i = 0; i < fileSize / recordSize; i++) {
        MainRecord r{};
        memcpy(&r, block + i * recordSize, recordSize);
        mainModel->addRecord(r);
    }
}
