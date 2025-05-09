#include "myticketstab.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QDebug>

MyTicketsTab::MyTicketsTab(int userId, const QString& role, QWidget *parent)
    : QWidget(parent), userId(userId), userRole(role) {
    table = new QTableView(this);
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ID", "Название", "Приоритет", "Проект", "Статус"});

    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setStretchLastSection(true);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(table);
    setLayout(layout);

    loadTickets();
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
