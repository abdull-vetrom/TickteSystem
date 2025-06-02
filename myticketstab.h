#ifndef MYTICKETSTAB_H
#define MYTICKETSTAB_H

#include <QWidget>
#include <QTabWidget>
#include <QStandardItemModel>

namespace Ui {
class MyTicketsTab;
}

class MyTicketsTab : public QWidget {
    Q_OBJECT

public:
    explicit MyTicketsTab(int userId, const QString& role, QTabWidget* tabWidget, QWidget* parent = nullptr);
    ~MyTicketsTab();
    void loadTickets();

private slots:
    void onCreateTicketClicked();
    void onTicketClicked(const QModelIndex& index);

private:
    Ui::MyTicketsTab* ui;

    int userId;
    QString userRole;
    QTabWidget* tabWidget;

    QStandardItemModel* model = nullptr;
    QStandardItemModel* doneModel = nullptr;

signals:
    void ticketsChanged();
};

#endif // MYTICKETSTAB_H
