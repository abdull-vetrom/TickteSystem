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

    ui->tabWidget->addTab(new MyTicketsTab(currentUserId, currentUserRole), "Мои тикеты");
    if (currentUserRole == "начальник" || currentUserRole == "работник") {
        ui->tabWidget->addTab(new MyProjectsTab(currentUserId, currentUserRole), "Мои проекты");
    }

    ui->tabWidget->addTab(new ProfileTab(currentUserId), "Мой профиль");

}
