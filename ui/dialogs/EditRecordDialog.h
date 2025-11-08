//
// Created by ivan on 11/7/25.
//

#ifndef LAB4_PA_QT_EDITRECORDDIALOG_H
#define LAB4_PA_QT_EDITRECORDDIALOG_H

#include <QDialog>

namespace Ui {
    class EditRecordDialog;
}

class EditRecordDialog final : public QDialog {
    Q_OBJECT

public:
    explicit EditRecordDialog(QWidget *parent = nullptr);

    void on_buttonBox_accepted();

    ~EditRecordDialog();

private:
    Ui::EditRecordDialog *ui;
};


#endif //LAB4_PA_QT_EDITRECORDDIALOG_H
