#include "ticketcard.h"
#include "ticket.h"
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TicketCard::TicketCard(int ticketId, QTabWidget* tabWidget, QWidget* parent)
    : QWidget(parent), ticketId(ticketId), tabWidget(tabWidget) {
    ui.setupUi(this);

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
}

void TicketCard::onEditClicked() {
    bool isVisible = ui.editPanel->isVisible();
    ui.editPanel->setVisible(!isVisible);

    if (!isVisible) {
        ui.editTitle->setText(ticket.title);

        QSqlQuery queryStatus("SELECT name FROM statuses");
        ui.editStatus->clear();
        while (queryStatus.next()) {
            ui.editStatus->addItem(queryStatus.value(0).toString());
        }
        ui.editStatus->setCurrentText(ticket.status);

        QSqlQuery queryPriority("SELECT name FROM priorities");
        ui.editPriority->clear();
        while (queryPriority.next()) {
            ui.editPriority->addItem(queryPriority.value(0).toString());
        }
        ui.editPriority->setCurrentText(ticket.priority);

        QSqlQuery queryUsers("SELECT full_name FROM users");
        ui.editAssignee->clear();
        while (queryUsers.next()) {
            ui.editAssignee->addItem(queryUsers.value(0).toString());
        }
        ui.editAssignee->setCurrentText(ticket.assignee);
    }
}

void TicketCard::onSaveClicked() {
    QString newTitle = ui.editTitle->text();
    QString newStatus = ui.editStatus->currentText();
    QString newPriority = ui.editPriority->currentText();
    QString newAssignee = ui.editAssignee->currentText();

    QSqlQuery statusQuery;
    statusQuery.prepare("SELECT id FROM statuses WHERE name = ?");
    statusQuery.addBindValue(newStatus);
    statusQuery.exec();
    int statusId = statusQuery.next() ? statusQuery.value(0).toInt() : -1;

    QSqlQuery priorityQuery;
    priorityQuery.prepare("SELECT id FROM priorities WHERE name = ?");
    priorityQuery.addBindValue(newPriority);
    priorityQuery.exec();
    int priorityId = priorityQuery.next() ? priorityQuery.value(0).toInt() : -1;

    QSqlQuery userQuery;
    userQuery.prepare("SELECT id FROM users WHERE full_name = ?");
    userQuery.addBindValue(newAssignee);
    userQuery.exec();
    int assigneeId = userQuery.next() ? userQuery.value(0).toInt() : -1;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE tickets SET title = ?, status_id = ?, priority_id = ?, assignee_id = ? WHERE id = ?");
    updateQuery.addBindValue(newTitle);
    updateQuery.addBindValue(statusId);
    updateQuery.addBindValue(priorityId);
    updateQuery.addBindValue(assigneeId);
    updateQuery.addBindValue(ticketId);

    if (!updateQuery.exec()) {
        qDebug() << "Ошибка обновления тикета:" << updateQuery.lastError().text();
    } else {
        qDebug() << "Тикет успешно обновлён.";
        emit ticketUpdated();  // <--- отправляем сигнал
        ui.editPanel->setVisible(false);
    }
}

void TicketCard::onBackClicked() {
    emit ticketUpdated();  // <--- отправляем сигнал перед выходом
    if (tabWidget) {
        int index = tabWidget->indexOf(this);
        if (index != -1)
            tabWidget->removeTab(index);
    }
}
