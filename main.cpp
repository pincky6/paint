#include "paintwidget.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintWidget w;
    w.show();
    return a.exec();
}
