#include "myticketstab.h"
#include "ui_myticketstab.h"
#include "createticketdialog.h"
#include "utils.h"
#include "ticketcard.h"
#include "prioritydelegate.h"
#include "mainwindow.h"
#include "profiletab.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QHeaderView>
#include <QDebug>

MyTicketsTab::MyTicketsTab(int userId_, const QString& role_, QTabWidget* tabWidget_, QWidget* parent)
    : QWidget(parent),
    ui(new Ui::MyTicketsTab),
    userId(userId_),
    userRole(role_),
    tabWidget(tabWidget_)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Название", "Проект", "Приоритет", "Статус"});
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->tableView, &QTableView::clicked, this, &MyTicketsTab::onTicketClicked);

    if (userRole != "начальник") {
        ui->createTicketButton->hide();
        ui->doneTableView->hide();
        ui->labelDone->hide();
    } else {
        connect(ui->createTicketButton, &QPushButton::clicked, this, &MyTicketsTab::onCreateTicketClicked);

        doneModel = new QStandardItemModel(this);
        doneModel->setHorizontalHeaderLabels({"Название", "Проект", "Приоритет", "Статус"});
        ui->doneTableView->setModel(doneModel);
        ui->doneTableView->horizontalHeader()->setStretchLastSection(true);
        ui->doneTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->doneTableView->verticalHeader()->setVisible(false);
        ui->doneTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->doneTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        connect(ui->doneTableView, &QTableView::clicked, this, &MyTicketsTab::onTicketClicked);
    }

    loadTickets();
}

MyTicketsTab::~MyTicketsTab() {
    delete ui;
}

void MyTicketsTab::onCreateTicketClicked() {
    CreateTicketDialog* dialog = new CreateTicketDialog(userId, this);
    connect(dialog, &CreateTicketDialog::ticketCreated, this, &MyTicketsTab::loadTickets);

    if (auto* mw = qobject_cast<MainWindow*>(window()); mw && mw->profileTab)
        connect(dialog, &CreateTicketDialog::ticketCreated, mw->profileTab, &ProfileTab::refreshStats);

    dialog->exec();
    delete dialog;
}

void MyTicketsTab::onTicketClicked(const QModelIndex& index) {
    if (!index.isValid()) return;

    int row = index.row();
    const QAbstractItemModel* source = index.model();

    int ticketId = -1;
    if (source == model)
        ticketId = model->item(row, 0)->data(Qt::UserRole).toInt();
    else if (doneModel && source == doneModel)
        ticketId = doneModel->item(row, 0)->data(Qt::UserRole).toInt();

    if (ticketId < 0) return;

    TicketCard* card = new TicketCard(ticketId, userId, tabWidget, this);
    tabWidget->addTab(card, QString("Тикет #%1").arg(ticketId));
    tabWidget->setCurrentWidget(card);

    connect(card, &TicketCard::ticketUpdated, this, &MyTicketsTab::loadTickets);

    if (auto* mw = qobject_cast<MainWindow*>(card->window()); mw && mw->profileTab)
        connect(card, &TicketCard::ticketUpdated, mw->profileTab, &ProfileTab::refreshStats);
}

void MyTicketsTab::loadTickets() {
    model->removeRows(0, model->rowCount());

    QSqlQuery query;
    query.prepare(loadSqlQuery(":/sql/getUserTickets.sql"));
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        return;
    }

    QList<QList<QStandardItem*>> rows;
    QMap<QString, int> priorityOrder = {
        {"Немедленный", 0},
        {"Высокий", 1},
        {"Средний", 2},
        {"Низкий", 3}
    };

    while (query.next()) {
        int ticketId = query.value(0).toInt();
        QString priority = query.value(3).toString();

        QList<QStandardItem*> row;
        for (int i = 1; i <= 4; ++i) {
            QStandardItem* item = new QStandardItem(query.value(i).toString());
            if (i == 1) item->setData(ticketId, Qt::UserRole);
            row.append(item);
        }

        int order = priorityOrder.value(priority, 99);
        row.first()->setData(order, Qt::UserRole + 1);
        rows.append(row);
    }

    std::sort(rows.begin(), rows.end(), [](const QList<QStandardItem*>& a, const QList<QStandardItem*>& b) {
        return a.first()->data(Qt::UserRole + 1).toInt() < b.first()->data(Qt::UserRole + 1).toInt();
    });

    for (const QList<QStandardItem*>& row : rows)
        model->appendRow(row);

    ui->tableView->setItemDelegate(new PriorityDelegate(this));

    if (userRole != "начальник") return;

    doneModel->removeRows(0, doneModel->rowCount());

    QSqlQuery doneQuery;
    doneQuery.prepare(loadSqlQuery(":/sql/getUserDoneTickets.sql"));
    doneQuery.bindValue(":userId", userId);

    if (doneQuery.exec()) {
        while (doneQuery.next()) {
            QList<QStandardItem*> row;
            int ticketId = doneQuery.value(0).toInt();
            for (int i = 1; i <= 4; ++i) {
                QStandardItem* item = new QStandardItem(doneQuery.value(i).toString());
                item->setBackground(QColor("#E8E8E8"));
                if (i == 1) {
                    QFont font = item->font();
                    font.setStrikeOut(true);
                    item->setFont(font);
                    item->setData(ticketId, Qt::UserRole);
                }
                row.append(item);
            }
            doneModel->appendRow(row);
        }
    }

    ui->labelDone->show();
    ui->doneTableView->show();
}
