#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableWidget>
#include "../core/index.h"
#include "IndexRecordModel.h"
#include "MainRecordModel.h"
#include "../core/main_area.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void onRecordAdd();

    void onIndexBlockChanged();

    void syncDataToIndexView(const std::vector<char> &block);

    void syncDataToMainView(const char *block);

private:
    Ui::MainWindow *ui;
    IndexArea index;
    MainArea mainArea;
    RecordModel *indexModel;
    MainRecordModel *mainModel;
    size_t indexBlockPage;
};
#endif // MAINWINDOW_H
