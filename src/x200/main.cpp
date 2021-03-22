#include "corevantage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    corevantage w;
    w.show();
    return a.exec();
}
