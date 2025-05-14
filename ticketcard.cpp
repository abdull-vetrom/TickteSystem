#include "ticketcard.h"
#include <QListWidgetItem>

TicketCard::TicketCard(int ticketId, QWidget* parent)
    : QDialog(parent) {
    ui.setupUi(this);

    Ticket ticket;
    if (!ticket.load(ticketId)) {
        reject();
        return;
    }

    ui.ticketTitleLabel->setText(ticket.title);
    ui.ticketDescription->setPlainText(ticket.description);
    ui.labelProjectValue->setText(ticket.project);
    ui.labelTrackerValue->setText(ticket.tracker);
    ui.labelTitleValue->setText(ticket.title);
    ui.labelStatusValue->setText(ticket.status);
    ui.labelPriorityValue->setText(ticket.priority);
    ui.labelAssignedValue->setText(ticket.assignee);
    ui.labelObserverValue->setText(ticket.watcher);

    for (const QString& file : ticket.attachments)
        ui.fileList->addItem(new QListWidgetItem(file));
}
