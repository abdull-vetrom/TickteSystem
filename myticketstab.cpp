#include "myticketstab.h"
#include "createticketdialog.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QPushButton>
#include <QTableView>
#include <QMessageBox>
#include <QDialog>


MyTicketsTab::MyTicketsTab(int userId, const QString& role_, QWidget* parent)
    : QWidget(parent), userId(userId), role(role_) {

    QVBoxLayout* layout = new QVBoxLayout(this);
    table = new QTableView(this);
    layout->addWidget(table);

    if (role == "начальник") {
        createTicketButton = new QPushButton("Создать тикет", this);
        layout->addWidget(createTicketButton);
        connect(createTicketButton, &QPushButton::clicked, this, &MyTicketsTab::onCreateTicketClicked);
    }

    loadTickets();
}

void MyTicketsTab::onCreateTicketClicked() {
    CreateTicketDialog *dialog = new CreateTicketDialog(userId, this);
    connect(dialog, &CreateTicketDialog::ticketCreated, this, &MyTicketsTab::loadTickets);
    dialog->exec();
    delete dialog;
}


void MyTicketsTab::loadTickets() {
    QSqlQuery query;
    QString sql = "SELECT id, title, priority, project, status FROM tickets WHERE ";

    if (userRole == "распределитель") {
        sql += "assigned_to = (SELECT full_name FROM users WHERE id = " + QString::number(userId) + ")";
    } else {
        sql += "assigned_to = (SELECT full_name FROM users WHERE id = " + QString::number(userId) + ") "
                                                                                                    "OR observer = (SELECT full_name FROM users WHERE id = " + QString::number(userId) + ")";
    }

    if (!query.exec(sql)) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QList<QStandardItem*> row;
        for (int i = 0; i < 5; ++i)
            row.append(new QStandardItem(query.value(i).toString()));
        model->appendRow(row);
    }
}
