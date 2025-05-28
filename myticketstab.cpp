#include "myticketstab.h"
#include "createticketdialog.h"
#include "utils.h"
#include "ticketcard.h"
#include "prioritydelegate.h"
#include "mainwindow.h"
#include "profiletab.h"

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

MyTicketsTab::MyTicketsTab(int userId, const QString& role_, QTabWidget* tabWidget_, QWidget* parent)
    : QWidget(parent),
    userId(userId),
    role(role_),
    userRole(role_),
    tabWidget(tabWidget_)  // ← сохраняем tabWidget
{
    ui.setupUi(this);

    ui.labelDone->hide();
    ui.doneTableView->hide();

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Название", "Проект", "Приоритет", "Статус"});
    ui.tableView->setModel(model);
    ui.tableView->horizontalHeader()->setStretchLastSection(true);
    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tableView->verticalHeader()->setVisible(false);

    if (userRole == "начальник") {
        createTicketButton = new QPushButton("Создать тикет", this);
        layout()->addWidget(createTicketButton);
        connect(createTicketButton, &QPushButton::clicked, this, &MyTicketsTab::onCreateTicketClicked);
    }

    connect(ui.tableView, &QTableView::clicked, this, &MyTicketsTab::onTicketClicked);
    connect(ui.doneTableView, &QTableView::clicked, this, &MyTicketsTab::onTicketClicked);

    loadTickets();
}


void MyTicketsTab::onCreateTicketClicked() {
    CreateTicketDialog *dialog = new CreateTicketDialog(userId, this);
    connect(dialog, &CreateTicketDialog::ticketCreated, this, &MyTicketsTab::loadTickets);

    MainWindow* mw = qobject_cast<MainWindow*>(window());
    if (mw && mw->profileTab)
        connect(dialog, &CreateTicketDialog::ticketCreated, mw->profileTab, &ProfileTab::refreshStats);

    dialog->exec();
    delete dialog;
}

void MyTicketsTab::onTicketClicked(const QModelIndex& index) {
    if (!index.isValid())
        return;

    int row = index.row();
    const QAbstractItemModel* sourceModel = index.model();

    int ticketId = -1;
    if (sourceModel == model) {
        ticketId = model->item(row, 0)->data(Qt::UserRole).toInt();
    } else if (sourceModel == doneModel) {
        ticketId = doneModel->item(row, 0)->data(Qt::UserRole).toInt();
    }

    if (ticketId < 0)
        return;

    TicketCard* window = new TicketCard(ticketId, userId, tabWidget, this);
    tabWidget->addTab(window, "Просмотр тикета");
    tabWidget->setCurrentWidget(window);

    connect(window, &TicketCard::ticketUpdated, this, &MyTicketsTab::loadTickets);

    MainWindow* mw = qobject_cast<MainWindow*>(window->window());
    if (mw && mw->profileTab) {
        connect(window, &TicketCard::ticketUpdated, mw->profileTab, &ProfileTab::refreshStats);
    }
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

    QList<QList<QStandardItem*>> unsortedRows;

    QMap<QString, int> priorityOrder = {
        {"Немедленный", 0},
        {"Высокий", 1},
        {"Средний", 2},
        {"Низкий", 3}
    };

    while (query.next()) {
        int ticketId = query.value(0).toInt();
        QString priorityValue = query.value(3).toString();

        QList<QStandardItem*> row;
        for (int i = 1; i <= 4; ++i) {
            QStandardItem* item = new QStandardItem(query.value(i).toString());
            if (i == 1) item->setData(ticketId, Qt::UserRole);
            row.append(item);
        }

        int order = priorityOrder.value(priorityValue, 99);
        row.first()->setData(order, Qt::UserRole + 1);
        unsortedRows.append(row);
    }

    std::sort(unsortedRows.begin(), unsortedRows.end(), [](const QList<QStandardItem*>& a, const QList<QStandardItem*>& b) {
        return a.first()->data(Qt::UserRole + 1).toInt() < b.first()->data(Qt::UserRole + 1).toInt();
    });

    for (const QList<QStandardItem*>& row : unsortedRows)
        model->appendRow(row);

    ui.tableView->setItemDelegate(new PriorityDelegate(this));

    // ===== Дополнительная таблица "Завершённые задачи" =====
    if (userRole != "начальник") {
        ui.doneTableView->hide();
        ui.labelDone->hide();
        return;
    }

    // Подготовка модели
    if (!doneModel)
        doneModel = new QStandardItemModel(this);

    doneModel->clear();
    doneModel->setHorizontalHeaderLabels({"Название", "Проект", "Приоритет", "Статус"});
    ui.doneTableView->setModel(doneModel);

    // Настройки внешнего вида, как у основной таблицы
    ui.doneTableView->horizontalHeader()->setStretchLastSection(true);
    ui.doneTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.doneTableView->verticalHeader()->setVisible(false);
    ui.doneTableView->setShowGrid(true);
    ui.doneTableView->setAlternatingRowColors(false);

    QSqlQuery doneQuery;
    QString doneSql = loadSqlQuery(":/sql/getUserDoneTickets.sql");
    doneQuery.prepare(doneSql);
    doneQuery.bindValue(":userId", userId);

    if (doneQuery.exec()) {
        while (doneQuery.next()) {
            QList<QStandardItem*> row;
            int ticketId = doneQuery.value(0).toInt();  // <- важно: сохраняем ID
            for (int i = 1; i <= 4; ++i) {
                QStandardItem* item = new QStandardItem(doneQuery.value(i).toString());
                item->setBackground(QColor("#E8E8E8"));
                if (i == 1) {
                    QFont font = item->font();
                    font.setStrikeOut(true);
                    item->setFont(font);
                    item->setData(ticketId, Qt::UserRole);  // <- сохраняем ID в название
                }
                row.append(item);
            }
            doneModel->appendRow(row);
        }
    }

    ui.labelDone->show();
    ui.doneTableView->show();
}



