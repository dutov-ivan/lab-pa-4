#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow), index("index"), mainArea("main", sizeof(MainRecord)) {
    ui->setupUi(this);
    ui->recordKeyLineEdit->setValidator((new QIntValidator(0, 100000, this)));
    ui->nameColumnLineEdit->setMaxLength(50);
    connect(ui->addRecordButton, &QPushButton::clicked, this, &MainWindow::onRecordAdd);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onRecordAdd() {
    bool ok;
    int recordKey = ui->recordKeyLineEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer");
        return;
    }

    std::string name = ui->nameColumnLineEdit->text().toStdString();
    const size_t nextRecordCount = mainArea.getRecordCount() + 1;
    index.addRecord(recordKey, nextRecordCount);

    MainRecord record;
    record.key = recordKey;

    std::memcpy(record.name, name.data(), std::min(name.size(), sizeof(record.name)));
    mainArea.writeRecord(record);
}
