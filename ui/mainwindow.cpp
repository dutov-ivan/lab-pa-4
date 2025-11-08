#include "mainwindow.h"
#include "forms/ui_mainwindow.h"
#include <QMessageBox>
#include <QStandardItemModel>

#include "core/utils.h"
#include "dialogs/AddRecordDialog.h"
#include "dialogs/DeleteRecordDialog.h"
#include "dialogs/EditRecordDialog.h"
#include "dialogs/GenerateRecordsDialog.h"
#include "dialogs/SearchRecordsDialog.h"

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


    connect(ui->addRecordButton, &QPushButton::clicked, this, &MainWindow::onAddRecord);
    connect(ui->editRecordButton, &QPushButton::clicked, this, &MainWindow::onEditRecord);
    connect(ui->deleteRecordButton, &QPushButton::clicked, this, &MainWindow::onDeleteRecord);
    connect(ui->generateRecordButton, &QPushButton::clicked, this, &MainWindow::onGenerateRecords);
    connect(ui->searchRecordButton, &QPushButton::clicked, this, &MainWindow::onSearchRecords);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onIndexBlockChanged() {
    throw NotImplemented();
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

void MainWindow::refreshData() {
    const std::vector<char> indexData = index.readBlock(indexBlockPage);

    syncDataToIndexView(indexData);

    const char *mainData = mainArea.readAll();
    syncDataToMainView(mainData);
}

void MainWindow::onAddRecord() {
    AddRecordDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        throw NotImplemented();
    }
}

void MainWindow::onEditRecord() {
    EditRecordDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        throw NotImplemented();
    }
}

void MainWindow::onDeleteRecord() {
    DeleteRecordDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        throw NotImplemented();
    }
}

void MainWindow::onGenerateRecords() {
    GenerateRecordsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        throw NotImplemented();
    }
}

void MainWindow::onSearchRecords() {
    SearchRecordsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        throw NotImplemented();
    }
}
