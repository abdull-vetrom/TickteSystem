#include "createprojectdialog.h"
#include "ui_createprojectdialog.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>

CreateProjectDialog::CreateProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProjectDialog) {
    ui->setupUi(this);
}

CreateProjectDialog::~CreateProjectDialog() {
    delete ui;
}

void CreateProjectDialog::on_saveButton_clicked() {
    QString name = ui->titleEdit->text().trimmed();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название проекта не может быть пустым.");
        return;
    }

    int departmentId = 1;  // пока жёстко задаём, позже можно выбрать из выпадающего списка

    QSqlQuery query;
    query.prepare("INSERT INTO projects (name, department_id) VALUES (:name, :department_id)");
    query.bindValue(":name", name);
    query.bindValue(":department_id", departmentId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить проект:\n" + query.lastError().text());
        return;
    }

    accept();
}

