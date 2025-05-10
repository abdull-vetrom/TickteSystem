#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "dbmanager.h"
#include "utils.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QFile>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    if (!DBManager::connect("localhost", "ticket_system", "root", "toor")) {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
        exit(1);
    }
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_loginButton_clicked() {
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();
    attemptLogin(email, password);
}

void LoginWindow::attemptLogin(const QString& email, const QString& password) {
    QSqlQuery query;

    QString sql = loadSqlQuery(":/sql/getUserLoginInfo.sql");
    query.prepare(sql);
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        int userId = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString role = query.value(2).toString();

        MainWindow *mainWindow = new MainWindow(userId, name, role, this);
        mainWindow->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный email или пароль.");
    }
}
