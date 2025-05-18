#include "myticketstab.h"
#include "createticketdialog.h"
#include "utils.h"
#include "ticketcard.h"

#include <QHeaderView>
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QPushButton>
#include <QTableView>
#include <QMessageBox>
#include <QDialog>
#include <QStandardItemModel>

MyTicketsTab::MyTicketsTab(int userId, const QString& role_, QTabWidget* tabWidget, QWidget* parent)
    : QWidget(parent), userId(userId), role(role_), tabWidget(tabWidget) {

    ui.setupUi(this);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Название", "Проект", "Приоритет", "Статус"});
    ui.tableView->setModel(model);
    ui.tableView->horizontalHeader()->setStretchLastSection(true);
    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tableView->verticalHeader()->setVisible(false);

    if (role == "начальник") {
        createTicketButton = new QPushButton("Создать тикет", this);
        layout()->addWidget(createTicketButton);
        connect(createTicketButton, &QPushButton::clicked, this, &MyTicketsTab::onCreateTicketClicked);
    }

    connect(ui.tableView, &QTableView::clicked, this, &MyTicketsTab::onTicketClicked);

    loadTickets();
}

void MyTicketsTab::onCreateTicketClicked() {
    CreateTicketDialog *dialog = new CreateTicketDialog(userId, this);
    connect(dialog, &CreateTicketDialog::ticketCreated, this, &MyTicketsTab::loadTickets);
    dialog->exec();
    delete dialog;
}

void MyTicketsTab::onTicketClicked(const QModelIndex& index) {
    if (!index.isValid())
        return;

    int row = index.row();
    int ticketId = model->item(row, 0)->data(Qt::UserRole).toInt();

    TicketCard* window = new TicketCard(ticketId, userId, tabWidget, this);
    tabWidget->addTab(window, "Просмотр тикета");
    tabWidget->setCurrentWidget(window);
    connect(window, &TicketCard::ticketUpdated, this, &MyTicketsTab::loadTickets);

}

void MyTicketsTab::loadTickets() {
    model->removeRows(0, model->rowCount());

    QSqlQuery query;
    QString sql = loadSqlQuery(":/sql/getUserTickets.sql");

    query.prepare(sql);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int ticketId = query.value(0).toInt();
        QList<QStandardItem*> row;
        for (int i = 1; i <= 4; ++i) {
            QStandardItem* item = new QStandardItem(query.value(i).toString());
            if (i == 1) item->setData(ticketId, Qt::UserRole);  // сохраним ticketId
            row.append(item);
        }
        model->appendRow(row);
    }
}
