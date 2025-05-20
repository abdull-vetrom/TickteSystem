#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myticketstab.h"
#include "myprojectstab.h"
#include "profiletab.h"

MainWindow::MainWindow(int userId, const QString& name, const QString& role, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentUserId(userId),
    currentUserName(name),
    currentUserRole(role)
{
    ui->setupUi(this);
    setWindowTitle("Тикет-система — " + currentUserName + " (" + currentUserRole + ")");
    setupTabs();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupTabs() {
    // Сохраняем тикет-таб для дальнейшего доступа
    ticketsTab = new MyTicketsTab(currentUserId, currentUserRole, ui->tabWidget, this);
    ui->tabWidget->addTab(ticketsTab, "Мои тикеты");

    if (currentUserRole == "начальник" || currentUserRole == "работник") {
        MyProjectsTab* projectsTab = new MyProjectsTab(currentUserId, currentUserRole, ui->tabWidget);
        ui->tabWidget->addTab(projectsTab, "Мои проекты");

        // Подключаем сигнал обновления тикетов
        connect(projectsTab, &MyProjectsTab::ticketsInvalidated, ticketsTab, &MyTicketsTab::loadTickets);
    }

    ui->tabWidget->addTab(new ProfileTab(currentUserId), "Мой профиль");
}
