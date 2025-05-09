#ifndef MYTICKETSTAB_H
#define MYTICKETSTAB_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

class MyTicketsTab : public QWidget {
    Q_OBJECT
public:
    MyTicketsTab(int userId, const QString& role, QWidget *parent = nullptr);

private:
    int userId;
    QString userRole;
    QTableView* table;
    QStandardItemModel* model;

    void loadTickets();
};

#endif // MYTICKETSTAB_H
