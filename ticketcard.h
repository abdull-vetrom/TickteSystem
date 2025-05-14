#ifndef TICKETCARD_H
#define TICKETCARD_H

#include <QDialog>
#include "ui_ticketcard.h"
#include "ticket.h"

class TicketCard : public QDialog {
    Q_OBJECT

public:
    explicit TicketCard(int ticketId, QWidget* parent = nullptr);

private:
    Ui::TicketCard ui;
};

#endif // TICKETCARD_H
