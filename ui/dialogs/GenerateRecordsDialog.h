//
// Created by ivan on 11/7/25.
//

#ifndef LAB4_PA_QT_GENERATERECORDSDIALOG_H
#define LAB4_PA_QT_GENERATERECORDSDIALOG_H

#include <QDialog>

namespace Ui {
    class GenerateRecordsDialog;
}

class GenerateRecordsDialog final : public QDialog {
    Q_OBJECT

public:
    explicit GenerateRecordsDialog(QWidget *parent = nullptr);

    void on_buttonBox_accepted();

    ~GenerateRecordsDialog();

private:
    Ui::GenerateRecordsDialog *ui;
};


#endif //LAB4_PA_QT_GENERATERECORDSDIALOG_H
