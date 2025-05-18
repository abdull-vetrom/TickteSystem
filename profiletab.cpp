#include "profiletab.h"
#include "utils.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QPixmap>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QDebug>

ProfileTab::ProfileTab(int userId, QWidget *parent)
    : QWidget(parent), userId(userId) {
    // Информационные метки
    labelName = new QLabel(this);
    labelEmail = new QLabel(this);
    labelRole = new QLabel(this);
    labelDept = new QLabel(this);

    labelName->setStyleSheet("font-weight: bold; font-size: 14px;");
    labelEmail->setStyleSheet("font-size: 13px;");
    labelRole->setStyleSheet("font-size: 13px;");
    labelDept->setStyleSheet("font-size: 13px;");

    // Фото
    photoLabel = new QLabel(this);
    photoLabel->setFixedSize(120, 120);
    photoLabel->setStyleSheet("border: 1px solid gray; background: #f0f0f0;");
    photoLabel->setAlignment(Qt::AlignCenter);

    uploadPhotoButton = new QPushButton("Загрузить фото", this);
    connect(uploadPhotoButton, &QPushButton::clicked, this, &ProfileTab::onUploadPhotoClicked);

    // Блок фото (вертикально)
    QVBoxLayout* photoLayout = new QVBoxLayout;
    photoLayout->addWidget(photoLabel, 0, Qt::AlignHCenter);
    photoLayout->addWidget(uploadPhotoButton, 0, Qt::AlignHCenter);
    photoLayout->addStretch();

    // Блок текста
    QVBoxLayout* infoLayout = new QVBoxLayout;
    infoLayout->addWidget(labelName);
    infoLayout->addWidget(labelEmail);
    infoLayout->addWidget(labelRole);
    infoLayout->addWidget(labelDept);
    infoLayout->addStretch();

    // Основной макет
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(infoLayout, 3);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(photoLayout, 1);

    setLayout(mainLayout);
    loadProfile();
}

void ProfileTab::loadProfile() {
    QSqlQuery query;
    query.prepare(R"(
        SELECT first_name, middle_name, last_name, email, role, d.name AS department, photo_path
        FROM users u
        JOIN departments d ON u.department_id = d.id
        WHERE u.id = :id
    )");
    query.bindValue(":id", userId);

    if (query.exec() && query.next()) {
        QString firstName = query.value("first_name").toString();
        QString middleName = query.value("middle_name").toString();
        QString lastName  = query.value("last_name").toString();
        QString email     = query.value("email").toString();
        QString role      = query.value("role").toString();
        QString department = query.value("department").toString();
        QString photoPath = query.value("photo_path").toString();

        labelName->setText("👤 ФИО: " + lastName + " " + firstName + " " + middleName);
        labelEmail->setText("📧 Почта: " + email);
        labelRole->setText("🛡️ Роль: " + role);
        labelDept->setText("🏢 Отдел: " + department);

        if (!photoPath.isEmpty()) {
            QPixmap pix(photoPath);
            photoLabel->setPixmap(pix.scaled(photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    } else {
        qDebug() << "Ошибка загрузки профиля:" << query.lastError().text();
    }
}

void ProfileTab::onUploadPhotoClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Выбрать фото", "", "Images (*.png *.jpg *.jpeg)");
    if (fileName.isEmpty())
        return;

    QString destDir = QDir::currentPath() + "/images";
    QDir().mkpath(destDir);

    QString newFilePath = destDir + QString("/user_%1.png").arg(userId);
    QFile::remove(newFilePath);
    QFile::copy(fileName, newFilePath);

    QSqlQuery query;
    query.prepare("UPDATE users SET photo_path = :path WHERE id = :id");
    query.bindValue(":path", newFilePath);
    query.bindValue(":id", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка сохранения фото:" << query.lastError().text();
        return;
    }

    QPixmap pix(newFilePath);
    photoLabel->setPixmap(pix.scaled(photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
