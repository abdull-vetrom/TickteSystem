#ifndef TICKETCARD_H
#define TICKETCARD_H

#include <QWidget>
#include "ui_ticketcard.h"
#include "ticket.h"

class TicketCard : public QWidget {
    Q_OBJECT

public:
    explicit TicketCard(int ticketId, QWidget* parent = nullptr);

private:
    Ui::TicketCard ui;

private slots:
    void onEditClicked();
};

#endif // TICKETCARD_H
