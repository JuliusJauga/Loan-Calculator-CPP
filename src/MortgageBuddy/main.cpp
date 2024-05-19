#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList fontFiles = {
        ":/fonts/fonts/Roboto-Bold.ttf",
        ":/fonts/fonts/Roboto-Light.ttf",
        ":/fonts/fonts/Roboto-Regular.ttf",
        ":/fonts/fonts/Poppins-Black.ttf",
        ":/fonts/fonts/Poppins-Bold.ttf",
        ":/fonts/fonts/Poppins-Light.ttf",
        ":/fonts/fonts/Poppins-Medium.ttf",
        ":/fonts/fonts/Poppins-Regular.ttf",
        ":/fonts/fonts/Inter-VariableFont.ttf"
    };

    for (const QString &fontFile : fontFiles) {
        int fontId = QFontDatabase::addApplicationFont(fontFile);
        if (fontId == -1) {
            qWarning() << "Failed to load font:" << fontFile;
        }
    }


    QFile file(":/styles/styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString stylesheet = file.readAll();
        a.setStyleSheet(stylesheet);
        file.close();
    } else {
        qWarning() << "Could not open stylesheet file";
    }

    MainWindow w;
    w.setWindowTitle("Mortgage Buddy");
    QPixmap transparentPixmap(1, 1);
    transparentPixmap.fill(Qt::transparent);
    w.setWindowIcon(QIcon(transparentPixmap));
    w.setFixedSize(1500, 820);
    w.show();
    return a.exec();
}
