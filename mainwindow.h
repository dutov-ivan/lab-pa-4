#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "index.h"
#include "main_area.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void onRecordAdd();

private:
    Ui::MainWindow *ui;
    IndexArea index;
    MainArea mainArea;
};
#endif // MAINWINDOW_H
