#include "myprojectstab.h"
#include "utils.h"
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

MyProjectsTab::MyProjectsTab(int userId, const QString& role, QWidget *parent)
    : QWidget(parent), userId(userId), userRole(role) {
    list = new QListWidget(this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(list);
    setLayout(layout);

    loadProjects();
}

void MyProjectsTab::loadProjects() {
    list->clear();
    QSqlQuery query;

    QString sql;

    if (userRole == "начальник") {
        sql = loadSqlQuery(":/sql/getChiefProjects.sql");
    } else {
        sql = loadSqlQuery(":/sql/getEmployeeProjects.sql");
    }

    query.prepare(sql);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        list->addItem(query.value(0).toString());
    }
}

