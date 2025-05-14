#ifndef MYTICKETSTAB_H
#define MYTICKETSTAB_H

#include <QWidget>
#include <QStandardItemModel>
#include <QString>
#include <QPushButton>

#include "ui_tickettable.h"  // подключение UI, сгенерированного из tickettable.ui

class MyTicketsTab : public QWidget {
    Q_OBJECT
public:
    MyTicketsTab(int userId, const QString& role_, QWidget* parent = nullptr);

private slots:
    void onCreateTicketClicked();
    void onTicketClicked(const QModelIndex& index);

private:
    int userId;
    QString userRole;
    QString role;
    QStandardItemModel* model;

    Ui::TicketTableForm ui;  // объект для доступа к элементам из .ui-файла
    QPushButton* createTicketButton;
    void loadTickets();
};

#endif // MYTICKETSTAB_H
