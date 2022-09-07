#include <debugger.h>

#define DEBUG_FILENAME "debug.exe"

Debugger::Debugger(QString debugPath){
    this->debugPath = debugPath;
    this->resultParser = new GDBResultParser();
    this->process = new QProcess();

    qDebug()<<debugPath;
}

void Debugger::execute(QString cmd){

    cmd.append("\r\n");
    QString programPath = QDir::currentPath();
    QDir::setCurrent(debugPath);

    qDebug()<<"Processing cmd:"<<cmd;
    process->write(cmd.toLocal8Bit().data());

    process->waitForFinished(PROGRAM_STOP_TIME);   //程序并未finish，但调用waitForFinished等待命令执行完毕

    QString stdOutPutMessage = QString::fromLocal8Bit(process->readAllStandardOutput());
    QString stdErrorMessage = QString::fromLocal8Bit(process->readAllStandardError());
    emit backMsg(stdOutPutMessage);
    emit backMsg(stdErrorMessage);

    QDir::setCurrent(programPath);
}

void Debugger::setPath(QString path){
    this->debugPath = path;
    qDebug()<<"debugPath:"<<this->debugPath;
}

void Debugger::startProgram(){
    QString programPath = QDir::currentPath();
    QDir::setCurrent(debugPath);

    process->setProgram("gdb");
    process->setWorkingDirectory(this->debugPath);
    process->setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    process->setProcessChannelMode(QProcess::MergedChannels);

    this->process->start();

    if(process->waitForStarted()){
        qDebug()<<"program started.";
    }
    else{
        qDebug()<<"program start failed."<<process->errorString();
    }

    connect(this->process, &QProcess::readyRead, [=](){
        QString stdOutPutMessage = QString::fromLocal8Bit(process->readAllStandardOutput());
        resultParser->buffer = stdOutPutMessage.replace("\r\n", " ");
        resultParser->parseResult();
    });

    this->execute(QString("file %1").arg(DEBUG_FILENAME));
    this->execute(QString("set new-console on"));

    QDir::setCurrent(programPath);
//    process->waitForFinished(200);

//    QString stdOutPutMessage = QString::fromLocal8Bit(process->readAllStandardOutput());
//    QString stdErrorMessage = QString::fromLocal8Bit(process->readAllStandardError());
//    qDebug()<< stdOutPutMessage;
//    qDebug()<< stdErrorMessage;
//    emit backMsg(stdOutPutMessage);
//    emit backMsg(stdErrorMessage);
}

void Debugger::endProgram(){
    process->kill();
}

void Debugger::cmd_run(){
    this->execute(QString("run"));
}

void Debugger::cmd_continue(){
    this->execute(QString("continue"));
}

void Debugger::cmd_setBreakPoint(int lineNumber, QString fileName){
    this->execute(QString("b %1:%2").arg(QString::number(lineNumber)).arg(fileName));
    this->breakPoints.insert(lineNumber, this->resultParser->gdbResults.breakPointId);
}

void Debugger::cmd_setBreakPoint(int lineNumber){
    this->execute(QString("b %1").arg(QString::number(lineNumber)));
    this->breakPoints.insert(lineNumber, this->resultParser->gdbResults.breakPointId);
}

void Debugger::cmd_deleteBreakPoint(int lineNumber){
    QString breakPointId = QString::number(this->breakPoints.find(lineNumber).value());
    this->execute(QString("delete %1").arg(QString::number(lineNumber)));
    this->breakPoints.remove(lineNumber);
}

/*
 * Debugger::printVal(QString valName)
 * 输入：变量名
 * 返回值：变量的int值
 * 注：暂只支持搜索int类型数值
 */
int Debugger::printVal(QString valName){
    this->execute(QString("print %1").arg(valName));
    this->process->waitForFinished(PROGRAM_STOP_TIME);
    return this->resultParser->gdbResults.printValue;
}

/*
 * GDBResults Debugger::getResult()
 * 返回值格式参见gdbresultparser.h对于此类的声明
 */
GDBResults Debugger::getResult(){
    return this->resultParser->gdbResults;
}
