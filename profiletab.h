#pragma once

#include <QWidget>

namespace Ui {
class ProfileTab;
}

class ProfileTab : public QWidget {
    Q_OBJECT

public:
    explicit ProfileTab(int userId, QWidget *parent = nullptr);
    ~ProfileTab();

public slots:
    void refreshStats();

private slots:
    void onUploadPhotoClicked();

private:
    Ui::ProfileTab* ui;
    int userId;
    QString userRole;

    void loadProfile();
    void loadStatusStats();
    void loadPriorityStats();
    void loadProjectStats();
};
