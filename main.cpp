/****************************************************************************
** Gui to practice with Qt and OpenCV  
****************************************************************************/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
