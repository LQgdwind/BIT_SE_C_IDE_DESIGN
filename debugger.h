#ifndef EDEBUGGER_H
#define EDEBUGGER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QProcessEnvironment>
#include <gdbresultparser.h>

#define PROGRAM_STOP_TIME 50
#define DEBUG_PATH "C:/Users/Administrator/Desktop/testc/debug"

class Debugger : public QObject{
    Q_OBJECT

signals:
    void backMsg(QString msg);

public:
    Debugger(QString debugPath);
    void setPath(QString path);
    void startProgram();
    void endProgram();
    void execute(QString cmd);

    void cmd_run();
    void cmd_continue();

    void cmd_setBreakPoint(int lineNumber, QString fileName);   //未完成
    void cmd_setBreakPoint(int lineNumber);

    void cmd_deleteBreakPoint(int lineNumber);
    int printVal(QString valName);  // 没有解决泛型问题
    GDBResults getResult();
    GDBResultParser *resultParser;

private:
    QMap<int, int> breakPoints;
    bool isDebugging = false;
    QProcess *process;
    QString debugPath;
};


#endif // EDEBUGGER_H