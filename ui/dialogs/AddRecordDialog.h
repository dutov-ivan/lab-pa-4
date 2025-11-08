//
// Created by ivan on 11/7/25.
//

#ifndef LAB4_PA_QT_ADDDIALOG_H
#define LAB4_PA_QT_ADDDIALOG_H
#include <QDialog>

namespace Ui {
    class AddRecordDialog;
}

class AddRecordDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddRecordDialog(QWidget *parent = nullptr);

    void on_buttonBox_accepted();

    ~AddRecordDialog();

private:
    Ui::AddRecordDialog *ui;
};


#endif //LAB4_PA_QT_ADDDIALOG_H
