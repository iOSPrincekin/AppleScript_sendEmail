# 背景

在mac开发过程中，会遇到需要发送带有附件邮件的情况，最常见的就是用户想向我们发送带有log文件和问题描述的邮件，这就需要我们开发这一功能，我的这篇文章是针对Qt C++开发的同学，如果需要OC语言和Swift版的相对应功能的代码，可以回复我。

# 实现

```
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

```

# 使用

```
void MainWindow::on_pushButton_clicked()
{
   OnFeedback();
}
```
具体使用请参考Demo [AppleScript_sendEmail](https://codeload.github.com/iOSPrincekin/AppleScript_sendEmail/zip/master)
----
# 许可

PrincekinKlineFrame 是在Apache License 2.0协议下开发完成的. 关于细节请查看[Apache License 2.0协议](https://github.com/iOSPrincekin/PrincekinKlineFrame/blob/master/LICENSE)。
