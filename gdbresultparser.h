#ifndef GDBRESULTPARSER_H
#define GDBRESULTPARSER_H

#include <QObject>
#include <QDebug>
#include <QMap>

enum GDBResultStatus{
    RUNNING,
    AT_BREAKPOINT,
    EXITED,
    GOT_VALUE
};

class GDBResults{
public:
    GDBResultStatus status = RUNNING;   //默认值是RUNNING，程序进行中。
                                        //参考enum GDBResultStatus

    int breakPointId = -1;              //默认值是-1，目前程序停在的断点位置
    QString function = QString("");     //默认值是""，断点所在文件
    int line = -1;                      //默认值是-1，断点所在行
    QChar returnValue = '2';            //默认值是'2'(QChar)，程序的返回值

    int printValue = -35575;                //默认值是-35575，执行print操作得到的值
};

class GDBResultParser: public QObject{
    Q_OBJECT
public:
    QString buffer;
    GDBResults gdbResults;
    void printBuffer();
    void parseResult();
};

#endif // GDBRESULTPARSER_H
