#ifndef PROFILETAB_H
#define PROFILETAB_H

#include <QWidget>
#include <QLabel>

class ProfileTab : public QWidget {
    Q_OBJECT
public:
    ProfileTab(int userId, QWidget *parent = nullptr);

private:
    int userId;
    QLabel *labelName, *labelEmail, *labelRole, *labelDept;

    void loadProfile();
};

#endif // PROFILETAB_H
