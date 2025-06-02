#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myticketstab.h"
#include "myprojectstab.h"
#include <QMainWindow>
#include "profiletab.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(int userId, const QString& name, const QString& role, QWidget *parent = nullptr);
    ~MainWindow();
    ProfileTab* profileTab;
    MyProjectsTab* projectsTab = nullptr;

private:
    Ui::MainWindow *ui;
    int currentUserId;
    QString currentUserName;
    QString currentUserRole;
    MyTicketsTab* ticketsTab = nullptr;
    void setupTabs();

};

#endif // MAINWINDOW_H
