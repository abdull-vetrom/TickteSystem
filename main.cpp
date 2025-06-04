#include <QApplication>
#include "loginwindow.h"
#include "mailtest.h"

int main(int argc, char *argv[]) {
    testMail();
    QApplication app(argc, argv);

    QIcon appIcon(":/icons/app_icon.png");
    app.setWindowIcon(appIcon);

    LoginWindow login;
    login.show();

    return app.exec();
}
