#include "ticket.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

Ticket::Ticket() {}

bool Ticket::load(int id_) {
    id = id_;
    QSqlQuery query;
    query.prepare(R"(
        SELECT
            t.title,
            t.description,
            p.name AS project,
            tr.name AS tracker,
            s.name AS status,
            pr.name AS priority,
            u1.full_name AS assignee,
            u2.full_name AS watcher,
            t.attachment,
            t.created_at
        FROM tickets t
        JOIN projects p ON t.project_id = p.id
        JOIN trackers tr ON t.tracker_id = tr.id
        JOIN statuses s ON t.status_id = s.id
        JOIN priorities pr ON t.priority_id = pr.id
        JOIN users u1 ON t.assignee_id = u1.id
        JOIN users u2 ON t.watcher_id = u2.id
        WHERE t.id = :ticketId
    )");
    query.bindValue(":ticketId", id);

    if (!query.exec()) {
        qDebug() << "Ticket load error:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        title = query.value(0).toString();
        description = query.value(1).toString();
        project = query.value(2).toString();
        tracker = query.value(3).toString();
        status = query.value(4).toString();
        priority = query.value(5).toString();
        assignee = query.value(6).toString();
        watcher = query.value(7).toString();
        attachments = query.value(8).toString().split(';', Qt::SkipEmptyParts);
        createdAt = query.value(9).toString();
        return true;
    }

    return false;
}
