#ifndef MYPROJECTSTAB_H
#define MYPROJECTSTAB_H

#include <QWidget>
#include <QListWidget>

class MyProjectsTab : public QWidget {
    Q_OBJECT
public:
    MyProjectsTab(int userId, const QString& role, QWidget *parent = nullptr);

private:
    int userId;
    QString userRole;
    QListWidget* list;

    void loadProjects();
};

#endif // MYPROJECTSTAB_H
