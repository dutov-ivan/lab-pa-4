//
// Created by ivan on 11/8/25.
//

#ifndef LAB4_PA_QT_DELETERECORDDIALOG_H
#define LAB4_PA_QT_DELETERECORDDIALOG_H


#include <QDialog>

namespace Ui {
    class DeleteRecordDialog;
}

class DeleteRecordDialog final : public QDialog {
    Q_OBJECT

public:
    explicit DeleteRecordDialog(QWidget *parent = nullptr);

    void on_buttonBox_accepted();

    ~DeleteRecordDialog();

    size_t getKeyToDelete();

private:
    Ui::DeleteRecordDialog *ui;
};


#endif //LAB4_PA_QT_DELETERECORDDIALOG_H
