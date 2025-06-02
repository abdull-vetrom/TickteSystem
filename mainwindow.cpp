#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabBar>

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
    ui->tabWidget->setTabsClosable(true); // Включаем крестики глобально

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index) {
        QWidget *tab = ui->tabWidget->widget(index);
        if (tab == ticketsTab || tab == projectsTab || tab == profileTab)
            return;

        ui->tabWidget->removeTab(index);
        delete tab;
    });

    ticketsTab = new MyTicketsTab(currentUserId, currentUserRole, ui->tabWidget, this);
    int ticketsIndex = ui->tabWidget->addTab(ticketsTab, "Мои тикеты");

    if (currentUserRole == "начальник" || currentUserRole == "работник") {
        projectsTab = new MyProjectsTab(currentUserId, currentUserRole, ui->tabWidget);
        int projectsIndex = ui->tabWidget->addTab(projectsTab, "Мои проекты");

        connect(projectsTab, &MyProjectsTab::ticketsInvalidated, ticketsTab, &MyTicketsTab::loadTickets);
        connect(ticketsTab, &MyTicketsTab::ticketsChanged, projectsTab, &MyProjectsTab::loadProjects);

        // Убираем крестик
        ui->tabWidget->tabBar()->setTabButton(projectsIndex, QTabBar::RightSide, nullptr);
    }

    profileTab = new ProfileTab(currentUserId);
    int profileIndex = ui->tabWidget->addTab(profileTab, "Мой профиль");

    // Убираем крестики с базовых вкладок
    ui->tabWidget->tabBar()->setTabButton(ticketsIndex, QTabBar::RightSide, nullptr);
    ui->tabWidget->tabBar()->setTabButton(profileIndex, QTabBar::RightSide, nullptr);
}
