#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <stdlib.h>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    OnFeedback();
}

void OnFeedback()
{
    string logName = "/Users/lee/Desktop/log.txt";     // 测试中log文件的位置，可以根据实际情况更换   不可使用 ~/Desktop
    string logPathStr = "\"" + logName + "\"";


            QString aScript =
                    QString(
                    "tell application \"Mail\"\n"
                        "set newMessage to (a reference to (make new outgoing message))\n"

                        "tell newMessage\n"
                            "make new recipient at beginning of to recipients ¬\n"
                                "with properties {address:\"15267030696@163.com\"}\n"

                            "set the subject to \"App---问题反馈\"\n"
                            "set the content to \"请描述您使用App遇到的问题：\\n\\n\\n\\n\\n\\n\\n\"\n"
                            "set color of content to {64614, 0, 111}\n"
                            "set size of content to 40\n"
                            "tell content\n"
                                "make new attachment ¬\n"
                                    "with properties {file name: %1 as string} ¬\n"
                                    "at after the last word of the last paragraph\n"
                            "end tell\n"
                            "set visible to true\n"
                        "activate application \"Mail\"\n"
                        "end tell\n"
                    "end tell\n").arg(logPathStr.c_str());

         cout << aScript.toStdString() << endl;

    QString osascript = "/usr/bin/osascript";
    QStringList processArguments;
    processArguments << "-l" << "AppleScript";

    QProcess p;
     p.start(osascript, processArguments);
     p.write(aScript.toUtf8());
     p.closeWriteChannel();
     p.waitForReadyRead(-1);
     QByteArray result = p.readAll();
     QString resultAsString(result); // if appropriate
     qDebug() << "the result of the script is" << resultAsString;
}

