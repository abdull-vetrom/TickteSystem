#include "profiletab.h"
#include "ui_profiletab.h"

#include "utils.h"
#include "storagemanager.h"
#include "addemployeedialog.h"
#include "userprofileeditdialog.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>

ProfileTab::ProfileTab(int userId_, QWidget *parent)
    : QWidget(parent), ui(new Ui::ProfileTab), userId(userId_) {
    ui->setupUi(this);

    ui->photoLabel->setFixedSize(180, 240);
    ui->photoLabel->setAlignment(Qt::AlignCenter);

    ui->addEmployeeButton->hide();  // скрыта по умолчанию

    connect(ui->uploadPhotoButton, &QPushButton::clicked,
            this, &ProfileTab::onUploadPhotoClicked);

    connect(ui->addEmployeeButton, &QPushButton::clicked, this, [this]() {
        AddEmployeeDialog dlg(userId, this);
        dlg.exec();
    });

    connect(ui->editProfileButton, &QPushButton::clicked, this, &ProfileTab::onEditProfileClicked);

    loadProfile();
}

ProfileTab::~ProfileTab() {
    delete ui;
}

void ProfileTab::loadProfile() {
    QSqlQuery query;
    QString sql = loadSqlQuery(":/sql/getUserProfileInfo.sql");
    query.prepare(sql);
    query.bindValue(":id", userId);

    if (!query.exec() || !query.next()) {
        qDebug() << "Ошибка загрузки профиля:" << query.lastError().text();
        return;
    }

    QString firstName = query.value("first_name").toString();
    QString middleName = query.value("middle_name").toString();
    QString lastName  = query.value("last_name").toString();
    QString email     = query.value("email").toString();
    QString role      = query.value("role").toString();
    QString department = query.value("department").toString();
    QString photoPath = query.value("photo_path").toString();

    userRole = role;

    ui->labelName->setText("👤 ФИО: " + lastName + " " + firstName + " " + middleName);
    ui->labelEmail->setText("📧 Почта: " + email);
    ui->labelRole->setText("🛡️ Роль: " + role);
    ui->labelDept->setText("🏢 Отдел: " + department);

    if (!photoPath.isEmpty()) {
        QPixmap pix(StorageManager::getAbsolutePath(photoPath));
        ui->photoLabel->setPixmap(pix.scaled(ui->photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->photoLabel->setText("");
    } else {
        ui->photoLabel->setText("Нет фото\nЗагрузите изображение");
        ui->photoLabel->setStyleSheet("QLabel { border: 1px dashed #aaa; color: #666; font-style: italic; }");
    }

    loadStatusStats();
    loadPriorityStats();

    if (role == "начальник") {
        loadProjectStats();
        ui->addEmployeeButton->show();
    }
}

void ProfileTab::onEditProfileClicked() {
    UserProfileEditDialog dialog(userId, this);
    if (dialog.exec() == QDialog::Accepted) {
        // Перезагрузить только текстовую информацию и фото, без статистики
        reloadPersonalInfo();
        refreshStats();  // Статистику — отдельно и только один раз
    }
}

void ProfileTab::reloadPersonalInfo() {
    QSqlQuery query;
    QString sql = loadSqlQuery(":/sql/getUserProfileInfo.sql");
    query.prepare(sql);
    query.bindValue(":id", userId);

    if (!query.exec() || !query.next()) {
        qDebug() << "Ошибка загрузки профиля:" << query.lastError().text();
        return;
    }

    QString firstName = query.value("first_name").toString();
    QString middleName = query.value("middle_name").toString();
    QString lastName  = query.value("last_name").toString();
    QString email     = query.value("email").toString();
    QString role      = query.value("role").toString();
    QString department = query.value("department").toString();
    QString photoPath = query.value("photo_path").toString();

    userRole = role;

    ui->labelName->setText("👤 ФИО: " + lastName + " " + firstName + " " + middleName);
    ui->labelEmail->setText("📧 Почта: " + email);
    ui->labelRole->setText("🛡️ Роль: " + role);
    ui->labelDept->setText("🏢 Отдел: " + department);

    if (!photoPath.isEmpty()) {
        QPixmap pix(StorageManager::getAbsolutePath(photoPath));
        ui->photoLabel->setPixmap(pix.scaled(ui->photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->photoLabel->setText("");
    } else {
        ui->photoLabel->setText("Нет фото\nЗагрузите изображение");
        ui->photoLabel->setStyleSheet("QLabel { border: 1px dashed #aaa; color: #666; font-style: italic; }");
    }
}

void ProfileTab::loadStatusStats() {
    QSqlQuery q;
    q.prepare(loadSqlQuery(":/sql/getUserTicketCountByStatus.sql"));
    q.bindValue(":userId", userId);
    q.exec();

    QGroupBox* box = new QGroupBox("Статистика задач (по статусам)");
    QVBoxLayout* layout = new QVBoxLayout(box);

    while (q.next()) {
        layout->addWidget(new QLabel(QString("%1: %2")
                                         .arg(q.value("status").toString(), q.value("count").toString())));
    }

    ui->statsLayout->addWidget(box);
}

void ProfileTab::loadPriorityStats() {
    QSqlQuery q;
    q.prepare(loadSqlQuery(":/sql/getUserTicketCountByPriority.sql"));
    q.bindValue(":userId", userId);
    q.exec();

    QGroupBox* box = new QGroupBox("Статистика задач (по приоритетам)");
    QVBoxLayout* layout = new QVBoxLayout(box);

    while (q.next()) {
        layout->addWidget(new QLabel(QString("%1: %2")
                                         .arg(q.value("priority").toString(), q.value("count").toString())));
    }

    ui->statsLayout->addWidget(box);
}

void ProfileTab::loadProjectStats() {
    QSqlQuery q;
    q.prepare(loadSqlQuery(":/sql/getUserDepartmentProjectStats.sql"));
    q.bindValue(":userId", userId);
    q.exec();

    QSqlQuery nameQuery;
    nameQuery.prepare(loadSqlQuery(":/sql/getDepartmentNameByUser.sql"));
    nameQuery.bindValue(":userId", userId);
    nameQuery.exec();
    nameQuery.next();

    QString deptName = nameQuery.value("department_name").toString();
    QGroupBox* box = new QGroupBox("Статистика по проектам (" + deptName + ")");
    QVBoxLayout* layout = new QVBoxLayout(box);

    while (q.next()) {
        layout->addWidget(new QLabel(QString("%1: %2")
                                         .arg(q.value("project").toString(), q.value("count").toString())));
    }

    ui->statsLayout->addWidget(box);
}

void ProfileTab::onUploadPhotoClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Выбрать фото", "", "Images (*.png *.jpg *.jpeg)");
    if (fileName.isEmpty()) return;

    QString relativePath = StorageManager::saveToStorage(fileName, "photos", QString("user_%1.png").arg(userId));
    if (relativePath.isEmpty()) {
        qDebug() << "Не удалось сохранить фото в storage";
        return;
    }

    QSqlQuery query;
    QString sql = loadSqlQuery(":/sql/updateUserProfilePhoto.sql");
    query.prepare(sql);
    query.bindValue(":path", relativePath);
    query.bindValue(":id", userId);
    if (!query.exec()) {
        qDebug() << "Ошибка сохранения фото:" << query.lastError().text();
        return;
    }

    QPixmap pix(StorageManager::getAbsolutePath(relativePath));
    ui->photoLabel->setPixmap(pix.scaled(ui->photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ProfileTab::refreshStats() {
    QLayoutItem* child;
    while ((child = ui->statsLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    loadStatusStats();
    loadPriorityStats();
    if (userRole == "начальник")
        loadProjectStats();
}
