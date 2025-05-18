#include "ticketcard.h"
#include "ticket.h"
#include "utils.h"
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QScrollBar>

TicketCard::TicketCard(int ticketId, int userId, QTabWidget* tabWidget, QWidget* parent)
    : QWidget(parent), ticketId(ticketId), userId(userId), tabWidget(tabWidget) {
    ui.setupUi(this);
    ui.historyScrollArea->setWidget(ui.historyScrollContents);
    if (!ticket.load(ticketId)) {
        close();
        return;
    }

    connect(ui.editButton, &QPushButton::clicked, this, &TicketCard::onEditClicked);
    connect(ui.backButton, &QPushButton::clicked, this, &TicketCard::onBackClicked);
    connect(ui.saveButton, &QPushButton::clicked, this, &TicketCard::onSaveClicked);

    QString fullTitle = QString("№%1  <b>%2</b>  (<i>%3</i>)")
                            .arg(ticket.id)
                            .arg(ticket.title)
                            .arg(ticket.tracker);
    ui.ticketTitleLabel->setText(fullTitle);
    ui.ticketTitleLabel->setAlignment(Qt::AlignCenter);
    ui.ticketTitleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    ui.ticketDescription->setPlainText(ticket.description);
    ui.ticketDescription->setReadOnly(true);
    ui.ticketDescription->document()->setTextWidth(ui.ticketDescription->viewport()->width());
    int maxHeight = 150;
    int contentHeight = static_cast<int>(ui.ticketDescription->document()->size().height());
    int finalHeight = qMin(contentHeight + 10, maxHeight);
    ui.ticketDescription->setMinimumHeight(finalHeight);
    ui.ticketDescription->setMaximumHeight(finalHeight);
    ui.ticketDescription->setStyleSheet("QTextEdit { background: transparent; border: none; }");

    ui.labelProjectValue->setText(ticket.project);
    ui.labelTrackerValue->setText(ticket.tracker);
    ui.labelStatusValue->setText(ticket.status);
    ui.labelPriorityValue->setText(ticket.priority);
    ui.labelAssignedValue->setText(ticket.assignee);
    ui.labelObserverValue->setText(ticket.watcher);

    int rowCount = ticket.attachments.size();
    for (const QString& file : ticket.attachments)
        ui.fileList->addItem(new QListWidgetItem(file));

    int fileListHeight = qMin(rowCount, 6) * 25 + 10;
    ui.fileList->setMinimumHeight(fileListHeight);
    ui.fileList->setMaximumHeight(fileListHeight);
    int totalHeight = fileListHeight + 40;
    ui.filesBox->setMinimumHeight(totalHeight);
    ui.filesBox->setMaximumHeight(totalHeight);

    ui.editPanel->setVisible(false);
    ui.editFooterPanel->setVisible(false);

    loadHistory();
}

void TicketCard::onEditClicked() {
    bool isVisible = ui.editPanel->isVisible();
    ui.editPanel->setVisible(!isVisible);
    ui.editFooterPanel->setVisible(!isVisible);

    if (!isVisible) {
        ui.editTitle->setText(ticket.title);

        QString sql;

        // Статусы
        sql = loadSqlQuery(":/sql/getStatusesIdAndName.sql");
        QSqlQuery queryStatus(sql);
        ui.editStatus->clear();
        statusMap.clear();
        while (queryStatus.next()) {
            int id = queryStatus.value("id").toInt();
            QString name = queryStatus.value("name").toString();
            ui.editStatus->addItem(name);
            statusMap[name] = id;
        }
        ui.editStatus->setCurrentText(ticket.status);

        // Приоритеты
        sql = loadSqlQuery(":/sql/getPrioritiesIdAndName.sql");
        QSqlQuery queryPriority(sql);
        ui.editPriority->clear();
        priorityMap.clear();
        while (queryPriority.next()) {
            int id = queryPriority.value("id").toInt();
            QString name = queryPriority.value("name").toString();
            ui.editPriority->addItem(name);
            priorityMap[name] = id;
        }
        ui.editPriority->setCurrentText(ticket.priority);

        // Пользователи (исполнители и наблюдатели)
        sql = loadSqlQuery(":/sql/getUsersIdAndFullName.sql");
        QSqlQuery queryUsers(sql);
        ui.editAssignee->clear();
        ui.editWatcher->clear(); // Добавлено
        userMap.clear();
        while (queryUsers.next()) {
            int id = queryUsers.value("id").toInt();
            QString name = queryUsers.value("full_name").toString();
            ui.editAssignee->addItem(name);
            ui.editWatcher->addItem(name); // Добавлено
            userMap[name] = id;
        }
        ui.editAssignee->setCurrentText(ticket.assignee);
        ui.editWatcher->setCurrentText(ticket.watcher); // Добавлено

        // Трекеры
        sql = loadSqlQuery(":/sql/getTrackersIdAndName.sql");
        QSqlQuery queryTrackers(sql);
        ui.editTracker->clear();
        trackerMap.clear();
        while (queryTrackers.next()) {
            int id = queryTrackers.value("id").toInt();
            QString name = queryTrackers.value("name").toString();
            ui.editTracker->addItem(name);
            trackerMap[name] = id;
        }
        ui.editTracker->setCurrentText(ticket.tracker); // Добавлено
    }
}


void TicketCard::onSaveClicked() {
    QString newTitle = ui.editTitle->text();
    QString newStatus = ui.editStatus->currentText();
    QString newPriority = ui.editPriority->currentText();
    QString newAssignee = ui.editAssignee->currentText();
    QString newWatcher = ui.editWatcher->currentText();
    QString newTracker = ui.editTracker->currentText();
    QString comment = ui.commentEdit->text().trimmed();

    int statusId = statusMap.value(newStatus, -1);
    int priorityId = priorityMap.value(newPriority, -1);
    int assigneeId = userMap.value(newAssignee, -1);
    int watcherId = userMap.value(newWatcher, -1);
    int trackerId = trackerMap.value(newTracker, -1);

    QString sql = loadSqlQuery(":/sql/updateTicketInfo.sql");
    QSqlQuery updateQuery;
    updateQuery.prepare(sql);
    updateQuery.bindValue(":title", newTitle);
    updateQuery.bindValue(":statusId", statusId);
    updateQuery.bindValue(":priorityId", priorityId);
    updateQuery.bindValue(":assigneeId", assigneeId);
    updateQuery.bindValue(":watcherId", watcherId);
    updateQuery.bindValue(":trackerId", trackerId);
    updateQuery.bindValue(":ticketId", ticketId);

    if (!updateQuery.exec()) {
        qDebug() << "Ошибка обновления тикета:" << updateQuery.lastError().text();
        return;
    }

    // Формирование изменений
    QStringList changes;

    auto track = [&](const QString& field, const QString& oldVal, const QString& newVal) {
        if (oldVal != newVal) {
            changes << QString("Параметр <b>%1</b> изменился с <i>%2</i> на <b>%3</b>")
                           .arg(field, oldVal, newVal);
        }
    };

    track("Название", ticket.title, newTitle);
    track("Статус", ticket.status, newStatus);
    track("Приоритет", ticket.priority, newPriority);
    track("Назначена", ticket.assignee, newAssignee);
    track("Наблюдатель", ticket.watcher, newWatcher);
    track("Трекер", ticket.tracker, newTracker);

    if (!changes.isEmpty() || !comment.isEmpty()) {
        QString historySql = loadSqlQuery(":/sql/saveTicketHistory.sql");
        QSqlQuery historyQuery;
        historyQuery.prepare(historySql);
        historyQuery.bindValue(":ticketId", ticketId);
        historyQuery.bindValue(":userId", userId);
        historyQuery.bindValue(":summary", changes.join("<br>"));
        historyQuery.bindValue(":comment", comment);
        historyQuery.bindValue(":changedAt", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

        if (!historyQuery.exec()) {
            qDebug() << "Ошибка записи единой истории:" << historyQuery.lastError().text();
        }
    }

    // Обновление UI
    ui.labelStatusValue->setText(newStatus);
    ui.labelPriorityValue->setText(newPriority);
    ui.labelAssignedValue->setText(newAssignee);
    ui.labelObserverValue->setText(newWatcher);
    ui.labelTrackerValue->setText(newTracker);

    QString updatedTitle = QString("№%1  <b>%2</b>  (<i>%3</i>)")
                               .arg(ticket.id)
                               .arg(newTitle)
                               .arg(newTracker);
    ui.ticketTitleLabel->setText(updatedTitle);

    ticket.title = newTitle;
    ticket.status = newStatus;
    ticket.priority = newPriority;
    ticket.assignee = newAssignee;
    ticket.watcher = newWatcher;
    ticket.tracker = newTracker;

    ui.editPanel->setVisible(false);
    ui.editFooterPanel->setVisible(false);
    ui.commentEdit->clear();

    emit ticketUpdated();
    loadHistory();
}

void TicketCard::loadHistory() {
    QString sql = loadSqlQuery(":/sql/getTicketHistoryByTicketId.sql");
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":ticketId", ticketId);
    if (!query.exec()) {
        qDebug() << "Ошибка истории:" << query.lastError().text();
        return;
    }

    // Очистка предыдущих виджетов истории
    QLayoutItem* child;
    while ((child = ui.historyLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Загрузка истории
    while (query.next()) {
        QString user = query.value("user").toString();
        QString timestamp = query.value("changed_at").toString();
        QString changesSummary = query.value("changes_summary").toString();
        QString comment = query.value("comment").toString();

        QString html = QString("<b>%1</b> (%2):<br>%3").arg(user, timestamp, changesSummary);
        if (!comment.isEmpty()) {
            html += QString("<br><i>%1</i>").arg(comment);
        }

        QLabel* label = new QLabel(html);
        label->setWordWrap(true);
        label->setTextFormat(Qt::RichText);
        ui.historyLayout->addWidget(label);
    }

    ui.historyScrollArea->setWidget(ui.historyScrollContents);

    if (QScrollBar* bar = ui.historyScrollArea->verticalScrollBar())
        bar->setValue(bar->maximum());
}

void TicketCard::onBackClicked() {
    emit ticketUpdated();

    if (tabWidget) {
        int index = tabWidget->indexOf(this);
        if (index != -1)
            tabWidget->removeTab(index);

        for (int i = 0; i < tabWidget->count(); ++i) {
            if (tabWidget->tabText(i) == "Мои тикеты") {
                tabWidget->setCurrentIndex(i);
                break;
            }
        }
    }
}
