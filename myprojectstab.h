#ifndef MYPROJECTSTAB_H
#define MYPROJECTSTAB_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>

class MyProjectsTab : public QWidget {
    Q_OBJECT
public:
    MyProjectsTab(int userId, const QString& role, QWidget *parent = nullptr);

private slots:
    void onCreateProjectClicked();
    void onDeleteProjectClicked();

private:
    int userId;
    QString userRole;
    QListWidget* list;
    QPushButton* createProjectButton;
    QPushButton* deleteProjectButton;

    void loadProjects();
};

#endif // MYPROJECTSTAB_H
