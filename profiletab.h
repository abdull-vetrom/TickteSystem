#ifndef PROFILETAB_H
#define PROFILETAB_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ProfileTab : public QWidget {
    Q_OBJECT
public:
    explicit ProfileTab(int userId, QWidget *parent = nullptr);

private slots:
    void onUploadPhotoClicked();

private:
    int userId;

    QLabel *labelName, *labelEmail, *labelRole, *labelDept;
    QLabel *photoLabel;
    QPushButton *uploadPhotoButton;

    void loadProfile();
};

#endif // PROFILETAB_H
