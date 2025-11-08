//
// Created by ivan on 11/8/25.
//

#ifndef LAB4_PA_QT_SEARCHRECORDSDIALOG_H
#define LAB4_PA_QT_SEARCHRECORDSDIALOG_H
#include <QDialog>

namespace Ui {
    class SearchRecordsDialog;
}

class SearchRecordsDialog final : public QDialog {
    Q_OBJECT

public:
    explicit SearchRecordsDialog(QWidget *parent = nullptr);

    void on_buttonBox_accepted();

    ~SearchRecordsDialog();

private:
    Ui::SearchRecordsDialog *ui;
};


#endif //LAB4_PA_QT_SEARCHRECORDSDIALOG_H
