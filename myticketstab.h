#ifndef MYTICKETSTAB_H
#define MYTICKETSTAB_H

#include <QWidget>
#include <QStandardItemModel>
#include <QString>
#include <QPushButton>
#include <QTabWidget>

#include "ui_tickettable.h"

class MyTicketsTab : public QWidget {
    Q_OBJECT
public:
    MyTicketsTab(int userId, const QString& role_, QTabWidget* tabWidget, QWidget* parent = nullptr);
    void loadTickets();

private slots:
    void onCreateTicketClicked();
    void onTicketClicked(const QModelIndex& index);

private:
    int userId;
    QString userRole;
    QString role;
    QStandardItemModel* model;
    QTabWidget* tabWidget = nullptr;

    Ui::TicketTableForm ui;
    QPushButton* createTicketButton;
    QStandardItemModel* doneModel = nullptr;
};

#endif // MYTICKETSTAB_H
