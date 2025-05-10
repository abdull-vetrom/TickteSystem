#include "createticketdialog.h"
#include "ui_createticketdialog.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDateTime>

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

    // Проекты
    if (query.exec("SELECT name FROM projects")) {
        while (query.next())
            ui->projectCombo->addItem(query.value(0).toString());
    }

    // Трекеры
    if (query.exec("SELECT name FROM trackers")) {
        while (query.next())
            ui->trackerCombo->addItem(query.value(0).toString());
    }

    // Статусы
    if (query.exec("SELECT name FROM statuses")) {
        while (query.next())
            ui->statusCombo->addItem(query.value(0).toString());
    }

    // Приоритеты
    if (query.exec("SELECT name FROM priorities")) {
        while (query.next())
            ui->priorityCombo->addItem(query.value(0).toString());
    }

    // Назначена — все пользователи
    if (query.exec("SELECT CONCAT(first_name, ' ', last_name) FROM users")) {
        while (query.next())
            ui->assigneeCombo->addItem(query.value(0).toString());
    }

    // Наблюдатель — по проекту
    updateWatchersByProject();
}

void CreateTicketDialog::updateWatchersByProject()
{
    ui->watcherCombo->clear();

    QSqlQuery query;
    query.prepare(R"(
        SELECT u.first_name, u.last_name
        FROM projects p
        JOIN departments d ON p.department_id = d.id
        JOIN users u ON u.department_id = d.id
        WHERE p.name = ?
    )");
    query.addBindValue(ui->projectCombo->currentText());

    if (query.exec()) {
        while (query.next()) {
            QString fullName = query.value(0).toString() + " " + query.value(1).toString();
            ui->watcherCombo->addItem(fullName);
        }
    }
}

void CreateTicketDialog::on_attachButton_clicked()
{
    attachedFilePath = QFileDialog::getOpenFileName(this, "Выбрать файл");
}

void CreateTicketDialog::on_cancelButton_clicked()
{
    reject();
}

void CreateTicketDialog::on_confirmButton_clicked()
{
    // Проверка обязательных полей
    if (ui->projectCombo->currentText().isEmpty() ||
        ui->trackerCombo->currentText().isEmpty() ||
        ui->titleEdit->text().isEmpty() ||
        ui->statusCombo->currentText().isEmpty() ||
        ui->priorityCombo->currentText().isEmpty() ||
        ui->assigneeCombo->currentText().isEmpty() ||
        ui->watcherCombo->currentText().isEmpty()) {
        showError("Пожалуйста, заполните все обязательные поля.");
        return;
    }

    QString title = ui->titleEdit->text();
    QString description = ui->descriptionEdit->toPlainText();
    QString projectName = ui->projectCombo->currentText();
    QString trackerName = ui->trackerCombo->currentText();
    QString statusName = ui->statusCombo->currentText();
    QString priorityName = ui->priorityCombo->currentText();
    QString assigneeFullName = ui->assigneeCombo->currentText();
    QString watcherFullName = ui->watcherCombo->currentText();
    QString startDate = ui->startDateEdit->date().toString(Qt::ISODate);

    // Подготовка подзапросов для получения id
    auto getId = [](const QString &table, const QString &column, const QString &value) -> int {
        QSqlQuery q;
        q.prepare(QString("SELECT id FROM %1 WHERE %2 = ?").arg(table, column));
        q.addBindValue(value);
        if (q.exec() && q.next())
            return q.value(0).toInt();
        return -1;
    };

    int projectId = getId("projects", "name", projectName);
    int trackerId = getId("trackers", "name", trackerName);
    int statusId = getId("statuses", "name", statusName);
    int priorityId = getId("priorities", "name", priorityName);
    int assigneeId = getId("users", "CONCAT(first_name, ' ', last_name)", assigneeFullName);
    int watcherId = getId("users", "CONCAT(first_name, ' ', last_name)", watcherFullName);

    if (projectId == -1 || trackerId == -1 || statusId == -1 || priorityId == -1 || assigneeId == -1 || watcherId == -1) {
        showError("Ошибка получения ID из справочников. Проверьте корректность данных.");
        return;
    }

    QSqlQuery insert;
    insert.prepare(R"(
        INSERT INTO tickets
        (title, description, project_id, tracker_id, status_id, priority_id, assignee_id, watcher_id, creator_id, start_date, attachment)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    )");

    insert.addBindValue(title);
    insert.addBindValue(description);
    insert.addBindValue(projectId);
    insert.addBindValue(trackerId);
    insert.addBindValue(statusId);
    insert.addBindValue(priorityId);
    insert.addBindValue(assigneeId);
    insert.addBindValue(watcherId);
    insert.addBindValue(userId);
    insert.addBindValue(startDate);
    insert.addBindValue(attachedFilePath);

    if (!insert.exec()) {
        showError("Ошибка добавления тикета: " + insert.lastError().text());
    } else {
        emit ticketCreated();
        accept();
    }
}


void CreateTicketDialog::showError(const QString &msg)
{
    QMessageBox::critical(this, "Ошибка", msg);
}
