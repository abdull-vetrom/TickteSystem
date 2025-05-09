#ifndef TICKET_H
#define TICKET_H

#include <QString>
#include <QDateTime>

struct Ticket {
    int id;
    QString title;
    QString description;
    QString senderEmail;
    QString tracker;
    QString status;
    QString project;
    QString assignedTo;
    QString observer;
    QString priority;
    QDateTime createdAt;

    Ticket();
};

#endif // TICKET_H
