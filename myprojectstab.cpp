#include "myprojectstab.h"
#include "utils.h"
#include "createprojectdialog.h"

#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>

MyProjectsTab::MyProjectsTab(int userId, const QString& role, QWidget *parent)
    : QWidget(parent), userId(userId), userRole(role) {
    list = new QListWidget(this);
    QVBoxLayout* layout = new QVBoxLayout;

    if (userRole == "начальник") {
        createProjectButton = new QPushButton("Создать проект", this);
        deleteProjectButton = new QPushButton("Удалить проект", this);

        layout->addWidget(createProjectButton);
        layout->addWidget(deleteProjectButton);

        connect(createProjectButton, &QPushButton::clicked, this, &MyProjectsTab::onCreateProjectClicked);
        connect(deleteProjectButton, &QPushButton::clicked, this, &MyProjectsTab::onDeleteProjectClicked);
    }

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

void MyProjectsTab::onCreateProjectClicked() {
    CreateProjectDialog dialog(this);  // важно передать текущий виджет как родителя
    dialog.setModal(true);
    if (dialog.exec() == QDialog::Accepted) {
        loadProjects();
    }
}

void MyProjectsTab::onDeleteProjectClicked() {
    QListWidgetItem* selectedItem = list->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Удаление", "Выберите проект для удаления.");
        return;
    }

    QString projectName = selectedItem->text();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Подтверждение удаления",
        "Удалить проект \"" + projectName + "\"?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply != QMessageBox::Yes)
        return;

    QSqlQuery query;
    query.prepare("DELETE FROM projects WHERE name = :name");
    query.bindValue(":name", projectName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить проект:\n" + query.lastError().text());
        return;
    }

    loadProjects();
}
