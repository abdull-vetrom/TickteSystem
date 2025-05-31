#ifndef MYPROJECTSTAB_H
#define MYPROJECTSTAB_H

#include <QWidget>
#include <QTabWidget>

namespace Ui {
class MyProjectsTab;
}

class MyProjectsTab : public QWidget {
    Q_OBJECT
public:
    explicit MyProjectsTab(int userId, const QString& role, QTabWidget* tabWidget, QWidget *parent = nullptr);
    ~MyProjectsTab();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void onCreateProjectClicked();
    void onDeleteProjectClicked();

private:
    Ui::MyProjectsTab* ui;

    int userId;
    QString userRole;
    QTabWidget* tabWidget;

    void loadProjects();

signals:
    void ticketsInvalidated();
};

#endif // MYPROJECTSTAB_H
