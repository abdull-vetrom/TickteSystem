#include "profiletab.h"
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>

ProfileTab::ProfileTab(int userId, QWidget *parent)
    : QWidget(parent), userId(userId) {
    labelName = new QLabel(this);
    labelEmail = new QLabel(this);
    labelRole = new QLabel(this);
    labelDept = new QLabel(this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(labelName);
    layout->addWidget(labelEmail);
    layout->addWidget(labelRole);
    layout->addWidget(labelDept);
    setLayout(layout);

    loadProfile();
}

void ProfileTab::loadProfile() {
    QSqlQuery query;
    query.prepare("SELECT full_name, email, role, department FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    if (query.exec() && query.next()) {
        labelName->setText("ФИО: " + query.value(0).toString());
        labelEmail->setText("Почта: " + query.value(1).toString());
        labelRole->setText("Роль: " + query.value(2).toString());
        labelDept->setText("Отдел: " + query.value(3).toString());
    }
}
