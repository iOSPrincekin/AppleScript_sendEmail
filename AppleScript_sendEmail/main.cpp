
#include <QApplication>
#include "mainwindow.h"

#include <QtCore>
inline const char* getCurrentDate_char_OnMacOS(){
    return   QDate::currentDate().toString("yyyy-MM-dd").toUtf8();
}

int main(int argc, char **argv)
{
  QApplication app(argc,argv);
  MainWindow M;
  M.show();
return app.exec();
}
