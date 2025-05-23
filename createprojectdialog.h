#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class CreateProjectDialog;
}

class CreateProjectDialog : public QDialog {
    Q_OBJECT

public:
    explicit CreateProjectDialog(QWidget *parent = nullptr);
    ~CreateProjectDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::CreateProjectDialog *ui;
};

#endif // CREATEPROJECTDIALOG_H
