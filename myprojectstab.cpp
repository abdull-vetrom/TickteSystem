#include "myprojectstab.h"
#include "ui_myprojectstab.h"
#include "utils.h"
#include "createprojectdialog.h"
#include "ticketcard.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QInputDialog>
#include <QEvent>
#include <QLabel>

MyProjectsTab::MyProjectsTab(int userId_, const QString& role, QTabWidget* tabWidget_, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::MyProjectsTab),
    userId(userId_),
    userRole(role),
    tabWidget(tabWidget_)
{
    ui->setupUi(this);

    if (userRole != "начальник") {
        ui->createProjectButton->hide();
        ui->deleteProjectButton->hide();
    } else {
        connect(ui->createProjectButton, &QPushButton::clicked, this, &MyProjectsTab::onCreateProjectClicked);
        connect(ui->deleteProjectButton, &QPushButton::clicked, this, &MyProjectsTab::onDeleteProjectClicked);
    }

    loadProjects();
}

MyProjectsTab::~MyProjectsTab() {
    delete ui;
}

void MyProjectsTab::loadProjects() {
    QLayoutItem* item;
    while ((item = ui->projectsLayout->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget()) delete w;
        delete item;
    }

    QSqlQuery query;
    QString sql = (userRole == "начальник")
                      ? loadSqlQuery(":/sql/getChiefProjects.sql")
                      : loadSqlQuery(":/sql/getEmployeeProjects.sql");

    query.prepare(sql);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString projectName = query.value("name").toString();
        int projectId = query.value("id").toInt();

        QWidget* projectWidget = new QWidget;
        QVBoxLayout* projectLayout = new QVBoxLayout(projectWidget);
        projectLayout->setContentsMargins(0, 0, 0, 0);

        QPushButton* toggleButton = new QPushButton("📁");
        toggleButton->setFlat(true);
        toggleButton->setCursor(Qt::PointingHandCursor);
        toggleButton->setStyleSheet("QPushButton { border: none; font-size: 16px; }");

        QLabel* titleLabel = new QLabel("<b>" + projectName + "</b>");
        QHBoxLayout* headerLayout = new QHBoxLayout;
        headerLayout->addWidget(toggleButton);
        headerLayout->addWidget(titleLabel);
        headerLayout->addStretch();

        QWidget* headerWidget = new QWidget;
        headerWidget->setLayout(headerLayout);
        projectLayout->addWidget(headerWidget);

        QWidget* ticketsContainer = new QWidget;
        QVBoxLayout* ticketsLayout = new QVBoxLayout(ticketsContainer);
        ticketsLayout->setContentsMargins(15, 5, 5, 5);
        ticketsContainer->setVisible(false);

        QSqlQuery ticketQuery;
        QString ticketSql = loadSqlQuery(":/sql/getTicketsByProject.sql");
        ticketQuery.prepare(ticketSql);
        ticketQuery.bindValue(":projectId", projectId);

        if (ticketQuery.exec()) {
            while (ticketQuery.next()) {
                int ticketId = ticketQuery.value("id").toInt();
                QString title = ticketQuery.value("title").toString();
                QString tracker = ticketQuery.value("tracker").toString();

                QLabel* ticketLabel = new QLabel(QString("#%1 | %2 [%3]").arg(ticketId).arg(title).arg(tracker));
                ticketLabel->setCursor(Qt::PointingHandCursor);
                ticketLabel->setStyleSheet("QLabel:hover { text-decoration: underline; }");
                ticketLabel->setProperty("ticketId", ticketId);
                ticketLabel->installEventFilter(this);
                ticketsLayout->addWidget(ticketLabel);
            }
        } else {
            ticketsLayout->addWidget(new QLabel("⚠ Ошибка загрузки тикетов"));
        }

        projectLayout->addWidget(ticketsContainer);

        connect(toggleButton, &QPushButton::clicked, this, [=]() mutable {
            bool isVisible = ticketsContainer->isVisible();
            ticketsContainer->setVisible(!isVisible);
            toggleButton->setText(isVisible ? "📁" : "📂");
        });

        ui->projectsLayout->addWidget(projectWidget);
    }

    ui->projectsLayout->addStretch();
}

bool MyProjectsTab::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseButtonRelease) {
        QLabel* label = qobject_cast<QLabel*>(obj);
        if (label && label->property("ticketId").isValid()) {
            int ticketId = label->property("ticketId").toInt();

            auto* card = new TicketCard(ticketId, userId, tabWidget, this);
            tabWidget->addTab(card, QString("Тикет #%1").arg(ticketId));
            tabWidget->setCurrentWidget(card);

            connect(card, &TicketCard::ticketUpdated, this, &MyProjectsTab::loadProjects);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void MyProjectsTab::onCreateProjectClicked() {
    CreateProjectDialog dialog(this);
    dialog.setModal(true);
    if (dialog.exec() == QDialog::Accepted) {
        loadProjects();
    }
}

void MyProjectsTab::onDeleteProjectClicked() {
    bool ok;
    QString projectName = QInputDialog::getText(this, "Удаление проекта", "Введите название проекта для удаления:",
                                                QLineEdit::Normal, "", &ok);
    if (!ok || projectName.trimmed().isEmpty()) return;

    QSqlQuery idQuery;
    QString idSql = loadSqlQuery(":/sql/getProjectIdByName.sql");
    idQuery.prepare(idSql);
    idQuery.bindValue(":name", projectName.trimmed());

    int projectId = -1;
    if (idQuery.exec() && idQuery.next()) {
        projectId = idQuery.value("id").toInt();
    } else {
        QMessageBox::warning(this, "Ошибка", "Проект с таким названием не найден.");
        return;
    }

    QSqlQuery query;
    QString sql = loadSqlQuery(":/sql/getTicketsByProject.sql");
    query.prepare(sql);
    query.bindValue(":projectId", projectId);

    QString ticketList;
    if (query.exec()) {
        while (query.next()) {
            int id = query.value("id").toInt();
            QString title = query.value("title").toString();
            QString tracker = query.value("tracker").toString();
            ticketList += QString("• #%1 | %2 [%3]\n").arg(id).arg(title).arg(tracker);
        }
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Подтверждение удаления",
                                                              QString("Вы уверены, что хотите удалить проект \"%1\"?\n\n"
                                                                      "Данному проекту принадлежат следующие тикеты:\n\n%2")
                                                                  .arg(projectName)
                                                                  .arg(ticketList.isEmpty() ? "(Нет тикетов)" : ticketList),
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) return;

    QStringList deletionSteps = {
        ":/sql/deleteTicketHistoryByProject.sql",
        ":/sql/deleteTicketFilesByProject.sql",
        ":/sql/deleteTicketsByProject.sql",
        ":/sql/deleteProject.sql"
    };

    for (const QString& path : deletionSteps) {
        QSqlQuery delQuery;
        QString stepSql = loadSqlQuery(path);
        delQuery.prepare(stepSql);
        delQuery.bindValue(":projectId", projectId);
        if (!delQuery.exec()) {
            QMessageBox::critical(this, "Ошибка", "Ошибка при удалении:\n" + delQuery.lastError().text());
            return;
        }
    }

    loadProjects();
    emit ticketsInvalidated();
}
