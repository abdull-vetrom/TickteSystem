#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QMap>
#include "ui_ticketcard.h"
#include "ticket.h"

class TicketCard : public QWidget {
    Q_OBJECT

public:
    explicit TicketCard(int ticketId, int userId, QTabWidget* tabWidget, QWidget* parent = nullptr);

signals:
    void ticketUpdated();

private:
    Ui::TicketCard ui;
    Ticket ticket;
    int ticketId;
    int userId;
    QTabWidget* tabWidget;

    QMap<QString, int> statusMap;
    QMap<QString, int> priorityMap;
    QMap<QString, int> userMap;
    QMap<QString, int> trackerMap;

private slots:
    void onEditClicked();
    void onBackClicked();
    void onSaveClicked();
    void loadHistory();
};
