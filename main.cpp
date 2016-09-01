#include <QApplication>
#include <QGridLayout>
#include "basewidget.h"

 int main ( int argc , char *argv[] )
{
    QApplication app(argc,argv);
    BaseWidget baseW;
    baseW.show();
    return app.exec();

}
