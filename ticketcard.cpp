#include "ticketcard.h"
#include <QListWidgetItem>

TicketCard::TicketCard(int ticketId, QWidget* parent)
    : QWidget(parent) {
    ui.setupUi(this);

    Ticket ticket;
    if (!ticket.load(ticketId)) {
        close();
        return;
    }

    // Скрываем панель редактирования по умолчанию
    // ui.editButton->setVisible(false);

    // Подключаем сигнал нажатия кнопки к слоту
    connect(ui.editButton, &QPushButton::clicked, this, &TicketCard::onEditClicked);


    // Заголовок: №id <название> (трекер)
    QString fullTitle = QString("№%1  <b>%2</b>  (<i>%3</i>)")
                            .arg(ticket.id)
                            .arg(ticket.title)
                            .arg(ticket.tracker);
    ui.ticketTitleLabel->setText(fullTitle);
    ui.ticketTitleLabel->setAlignment(Qt::AlignCenter);
    ui.ticketTitleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    // Описание
    ui.ticketDescription->setPlainText(ticket.description);
    ui.ticketDescription->setReadOnly(true);
    ui.ticketDescription->document()->setTextWidth(ui.ticketDescription->viewport()->width());

    int maxHeight = 150;
    int contentHeight = static_cast<int>(ui.ticketDescription->document()->size().height());
    int finalHeight = qMin(contentHeight + 10, maxHeight);
    ui.ticketDescription->setMinimumHeight(finalHeight);
    ui.ticketDescription->setMaximumHeight(finalHeight);
    ui.ticketDescription->setStyleSheet("QTextEdit { background: transparent; border: none; }");

    // Информация
    ui.labelProjectValue->setText(ticket.project);
    ui.labelTrackerValue->setText(ticket.tracker);
    ui.labelStatusValue->setText(ticket.status);
    ui.labelPriorityValue->setText(ticket.priority);
    ui.labelAssignedValue->setText(ticket.assignee);
    ui.labelObserverValue->setText(ticket.watcher);

    // Файлы
    int rowCount = ticket.attachments.size();
    for (const QString& file : ticket.attachments)
        ui.fileList->addItem(new QListWidgetItem(file));

    int fileListHeight = qMin(rowCount, 6) * 25 + 10;
    ui.fileList->setMinimumHeight(fileListHeight);
    ui.fileList->setMaximumHeight(fileListHeight);

    int totalHeight = fileListHeight + 40;
    ui.filesBox->setMinimumHeight(totalHeight);
    ui.filesBox->setMaximumHeight(totalHeight);
}

void TicketCard::onEditClicked() {
    // Переключаем видимость панели редактирования
    bool isVisible = ui.editPanel->isVisible();
    ui.editPanel->setVisible(!isVisible);

    if (!isVisible) {
        // Инициализируем значения полей редактирования текущими данными тикета
        ui.editStatus->setCurrentText(ui.labelStatusValue->text());
        ui.editPriority->setCurrentText(ui.labelPriorityValue->text());
        ui.editAssignee->setCurrentText(ui.labelAssignedValue->text());
        ui.editWatcher->setCurrentText(ui.labelObserverValue->text());
        ui.editTracker->setCurrentText(ui.labelTrackerValue->text());
        ui.editTitle->setText(ui.ticketTitleLabel->text());
    }
}
