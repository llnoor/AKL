#include <qapplication.h>
#include "mainwindow.h"
#include "dialog_k.h"

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow w;
    w.show();

    return a.exec();
}
