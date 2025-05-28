#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QMap>
#include <QLabel>
#include <QEvent>
#include "ui_ticketcard.h"
#include "ticket.h"

class TicketCard : public QWidget {
    Q_OBJECT

public:
    explicit TicketCard(int ticketId, int userId, QTabWidget* tabWidget, QWidget* parent = nullptr);

signals:
    void ticketUpdated();
    void ticketCreated();

private:
    Ui::TicketCard ui;
    Ticket ticket;
    int ticketId;
    int userId;
    QTabWidget* tabWidget;
    QStringList newlyAttachedFiles;

    QMap<QString, int> statusMap;
    QMap<QString, int> priorityMap;
    QMap<QString, int> userMap;
    QMap<QString, int> trackerMap;

    void addFileLabel(const QString& fileName);
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void onEditClicked();
    void onBackClicked();
    void onSaveClicked();
    void onAttachFileClicked();
    void loadHistory();
    void loadFiles();
};
