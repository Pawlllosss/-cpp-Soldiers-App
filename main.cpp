#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "MainWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
