#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Print current working directory
    // Use absolute path for testing
    QFile file(":/styles/styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString stylesheet = file.readAll();
        a.setStyleSheet(stylesheet);
        file.close();
    } else {
        qWarning() << "Could not open stylesheet file";
    }
    MainWindow w;
    w.show();
    return a.exec();
}
