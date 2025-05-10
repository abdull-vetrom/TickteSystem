#include "myticketstab.h"
#include "createticketdialog.h"
#include "utils.h"
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
#include <QStandardItemModel>

MyTicketsTab::MyTicketsTab(int userId, const QString& role_, QWidget* parent)
    : QWidget(parent), userId(userId), role(role_) {

    QVBoxLayout* layout = new QVBoxLayout(this);
    table = new QTableView(this);
    layout->addWidget(table);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Название", "Проект", "Приоритет", "Статус"});
    table->setModel(model);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
    model->removeRows(0, model->rowCount());

    QSqlQuery query;
    QString sql = loadSqlQuery(":/sql/getUserTickets.sql");

    query.prepare(sql);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QList<QStandardItem*> row;
        for (int i = 0; i < 4; ++i) { // Только 4 поля
            QStandardItem* item = new QStandardItem(query.value(i).toString());
            item->setEditable(false);
            row.append(item);
        }
        model->appendRow(row);
    }
}
