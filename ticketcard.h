#pragma once

#include <QWidget>
#include <QTabWidget>
#include "ui_ticketcard.h"
#include "ticket.h"

class TicketCard : public QWidget {
    Q_OBJECT

public:
    explicit TicketCard(int ticketId, QTabWidget* tabWidget, QWidget* parent = nullptr);

signals:
    void ticketUpdated();  // <--- добавлен сигнал

private:
    Ui::TicketCard ui;
    Ticket ticket;
    int ticketId;
    QTabWidget* tabWidget;

private slots:
    void onEditClicked();
    void onBackClicked();
    void onSaveClicked();
};
