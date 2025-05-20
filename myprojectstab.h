#ifndef MYPROJECTSTAB_H
#define MYPROJECTSTAB_H

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTabWidget>

class MyProjectsTab : public QWidget {
    Q_OBJECT
public:
    MyProjectsTab(int userId, const QString& role, QTabWidget* tabWidget, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void onCreateProjectClicked();
    void onDeleteProjectClicked();

private:
    int userId;
    QString userRole;
    QTabWidget* tabWidget;

    QPushButton* createProjectButton;
    QPushButton* deleteProjectButton;

    QScrollArea* scrollArea;
    QWidget* scrollContent;
    QVBoxLayout* projectsLayout;

    void loadProjects();

signals:
    void ticketsInvalidated();
};

#endif // MYPROJECTSTAB_H
