#include "tidepool.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    // mac directory fix
#ifdef Q_OS_MACOS
    QDir bin(QCoreApplication::applicationDirPath());
    bin.cdUp();
    bin.cdUp();
    bin.cdUp();
    QDir::setCurrent(bin.absolutePath());
#endif

    Tidepool w;
    w.show();
    return a.exec();
}
