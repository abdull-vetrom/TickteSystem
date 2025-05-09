#ifndef MYTICKETSTAB_H
#define MYTICKETSTAB_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>

class MyTicketsTab : public QWidget {
    Q_OBJECT
public:
    MyTicketsTab(int userId, const QString& role_, QWidget* parent = nullptr);

private slots:
    void onCreateTicketClicked();

private:
    int userId;
    QString userRole;
    QTableView* table;
    QStandardItemModel* model;
    QPushButton* createTicketButton;
    QString role;

    void loadTickets();
};




#endif // MYTICKETSTAB_H
