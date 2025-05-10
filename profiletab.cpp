#include "profiletab.h"
#include "utils.h"
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
    QString sql = loadSqlQuery(":/sql/getUserProfileInfo.sql");
    query.prepare(sql);
    query.bindValue(":id", userId);

    if (query.exec() && query.next()) {
        QString firstName = query.value("first_name").toString();
        QString lastName  = query.value("last_name").toString();
        QString email     = query.value("email").toString();
        QString role      = query.value("role").toString();
        QString department      = query.value("department").toString();

        labelName->setText("ФИО: " + firstName + " " + lastName);
        labelEmail->setText("Почта: " + email);
        labelRole->setText("Роль: " + role);
        labelDept->setText("Отдел: " + department);
    }
}
