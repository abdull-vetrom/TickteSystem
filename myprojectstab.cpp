#include "myprojectstab.h"
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>

MyProjectsTab::MyProjectsTab(int userId, const QString& role, QWidget *parent)
    : QWidget(parent), userId(userId), userRole(role) {
    list = new QListWidget(this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(list);
    setLayout(layout);

    loadProjects();
}

void MyProjectsTab::loadProjects() {
    QSqlQuery query;
    if (userRole == "начальник") {
        query.exec("SELECT DISTINCT project FROM tickets WHERE assigned_to IN "
                   "(SELECT full_name FROM users WHERE department = "
                   "(SELECT department FROM users WHERE id = " + QString::number(userId) + "))");
    } else {
        query.exec("SELECT DISTINCT project FROM tickets WHERE assigned_to = "
                   "(SELECT full_name FROM users WHERE id = " + QString::number(userId) + ")");
    }

    while (query.next()) {
        list->addItem(query.value(0).toString());
    }
}
