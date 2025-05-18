#include "createticketdialog.h"
#include "ui_createticketdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QVariantList>

CreateTicketDialog::CreateTicketDialog(int currentUserId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTicketDialog),
    userId(currentUserId)
{
    ui->setupUi(this);
    db = QSqlDatabase::database();
    ui->startDateEdit->setDate(QDate::currentDate());
    populateCombos();

    connect(ui->projectCombo, &QComboBox::currentTextChanged, this, &CreateTicketDialog::updateWatchersByProject);
}

CreateTicketDialog::~CreateTicketDialog()
{
    delete ui;
}

void CreateTicketDialog::populateCombos()
{
    QSqlQuery query;

    query.exec("SELECT id, name FROM projects");
    while (query.next()) {
        ui->projectCombo->addItem(query.value(1).toString(), query.value(0));
    }

    query.exec("SELECT id, name FROM trackers");
    while (query.next()) {
        ui->trackerCombo->addItem(query.value(1).toString(), query.value(0));
    }

    query.exec("SELECT id, name FROM statuses");
    while (query.next()) {
        ui->statusCombo->addItem(query.value(1).toString(), query.value(0));
    }

    query.exec("SELECT id, name FROM priorities");
    while (query.next()) {
        ui->priorityCombo->addItem(query.value(1).toString(), query.value(0));
    }

    updateWatchersByProject();
}

void CreateTicketDialog::updateWatchersByProject()
{
    ui->watcherCombo->clear();
    ui->assigneeCombo->clear();

    int projectId = ui->projectCombo->currentData().toInt();
    QSqlQuery query;
    query.prepare("SELECT department_id FROM projects WHERE id = ?");
    query.addBindValue(projectId);

    if (!query.exec() || !query.next()) {
        showError("Ошибка получения отдела проекта.");
        return;
    }

    int deptId = query.value(0).toInt();

    // Заполняем наблюдателей
    query.prepare("SELECT id, full_name FROM users WHERE department_id = ?");
    query.addBindValue(deptId);
    if (query.exec()) {
        while (query.next()) {
            ui->watcherCombo->addItem(query.value(1).toString(), query.value(0));
        }
    }

    // Заполняем исполнителей
    query.prepare("SELECT id, full_name FROM users WHERE department_id = ?");
    query.addBindValue(deptId);
    if (query.exec()) {
        while (query.next()) {
            ui->assigneeCombo->addItem(query.value(1).toString(), query.value(0));
        }
    }
}

void CreateTicketDialog::on_confirmButton_clicked()
{
    QString title = ui->titleEdit->text().trimmed();
    QString description = ui->descriptionEdit->toPlainText();
    int projectIndex = ui->projectCombo->currentIndex();
    int trackerIndex = ui->trackerCombo->currentIndex();
    int statusIndex = ui->statusCombo->currentIndex();
    int priorityIndex = ui->priorityCombo->currentIndex();

    // Проверка обязательных полей
    QString borderRed = "border: 1px solid red;";
    QString borderClear = "";

    bool valid = true;
    if (projectIndex == -1) {
        ui->projectCombo->setStyleSheet(borderRed);
        valid = false;
    } else {
        ui->projectCombo->setStyleSheet(borderClear);
    }

    if (trackerIndex == -1) {
        ui->trackerCombo->setStyleSheet(borderRed);
        valid = false;
    } else {
        ui->trackerCombo->setStyleSheet(borderClear);
    }

    if (statusIndex == -1) {
        ui->statusCombo->setStyleSheet(borderRed);
        valid = false;
    } else {
        ui->statusCombo->setStyleSheet(borderClear);
    }

    if (priorityIndex == -1) {
        ui->priorityCombo->setStyleSheet(borderRed);
        valid = false;
    } else {
        ui->priorityCombo->setStyleSheet(borderClear);
    }

    if (!valid) {
        showError("Пожалуйста, заполните все обязательные поля: проект, трекер, статус, приоритет.");
        return;
    }

    int projectId = ui->projectCombo->currentData().toInt();
    int trackerId = ui->trackerCombo->currentData().toInt();
    int statusId = ui->statusCombo->currentData().toInt();
    int priorityId = ui->priorityCombo->currentData().toInt();
    int assigneeId = ui->assigneeCombo->currentData().toInt();
    int watcherId = ui->watcherCombo->currentData().toInt();
    QDate startDate = ui->startDateEdit->date();
    QString attachment = attachedFilePath;

    if (title.isEmpty()) {
        showError("Введите заголовок тикета.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO tickets (title, description, project_id, tracker_id, status_id, priority_id, assignee_id, watcher_id, creator_id, start_date, attachment) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(title);
    query.addBindValue(description);
    query.addBindValue(projectId);
    query.addBindValue(trackerId);
    query.addBindValue(statusId);
    query.addBindValue(priorityId);
    query.addBindValue(assigneeId);
    query.addBindValue(watcherId);
    query.addBindValue(userId);
    query.addBindValue(startDate);
    query.addBindValue(attachment);

    if (!query.exec()) {
        showError("Ошибка при создании тикета: " + query.lastError().text());
        return;
    }

    emit ticketCreated();
    accept();
}

void CreateTicketDialog::on_cancelBtn_clicked()
{
    reject(); // Закрыть окно
}

void CreateTicketDialog::on_attachBtn_clicked()
{
    // Заглушка
}

void CreateTicketDialog::showError(const QString &msg)
{
    QMessageBox::critical(this, "Ошибка", msg);
}
