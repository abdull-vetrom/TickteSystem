#ifndef CREATETICKETDIALOG_H
#define CREATETICKETDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFileDialog>

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
    void on_cancelButton_clicked();
    void on_attachButton_clicked();
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
