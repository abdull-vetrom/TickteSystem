#ifndef CREATETICKETDIALOG_H
#define CREATETICKETDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class CreateTicketDialog;
}

class CreateTicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTicketDialog(int currentUserId, QWidget *parent = nullptr);
    ~CreateTicketDialog();

signals:
    void ticketCreated();

private slots:
    void on_confirmButton_clicked();
    void on_cancelBtn_clicked();
    void on_attachBtn_clicked();
    void updateWatchersByProject();

private:
    Ui::CreateTicketDialog *ui;
    QSqlDatabase db;
    int userId;
    QString attachedFilePath;

    void populateCombos();
    void showError(const QString &msg);
};

#endif // CREATETICKETDIALOG_H
