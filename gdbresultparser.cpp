#include <gdbresultparser.h>

enum StringType{
    UNDEFINED,
    BREAKPOINT_FLAG,
    FILE_FLAG,
    RETURN_VALUE_FLAG
};

//using for test
void GDBResultParser::printBuffer(){
    qDebug()<<"receive msg.";
    QStringList bufferCut = buffer.split(" ");
    qDebug()<<bufferCut;
}

//using for test
void printResult(GDBResults result){
    qDebug()<<"Status: "<<result.status;
    qDebug()<<"BreakPointId: "<<result.breakPointId;
    qDebug()<<"AtFunction: "<<result.function;
    qDebug()<<"Line: "<<result.line;
    qDebug()<<"ReturnValue: "<<result.returnValue;
    qDebug()<<"PrintValue: "<<result.printValue;
}

void GDBResultParser::parseResult(void){

    GDBResults result;
    qDebug()<<buffer;
    QStringList bufferCut = buffer
            .replace(",", " ")
            .split(" ");
    result.status = RUNNING;
    StringType stringType = UNDEFINED;

    for(int i = 0; i < bufferCut.size(); i++){

        QString it = bufferCut.at(i);

        if(it.contains(QString("$"))){
            result.printValue = bufferCut.at(i+2).toInt();
            break;
        }

//        qDebug()<<"Reading itStrings:"<<it;

//        qDebug()<<"i = "<<i;
//        qDebug()<<it;
//        qDebug()<<QString("Breakpoint");
//        qDebug()<<QString::compare(it, QString("Breakpoint"));

//        qDebug()<<"i = "<<i;
//        qDebug()<<"string type: "<<stringType;

        if(stringType == BREAKPOINT_FLAG){
            result.breakPointId = it.toInt();
            stringType = UNDEFINED;
        }
        else if(stringType == FILE_FLAG){
            QStringList tmp = it.split(":");
            result.function = tmp[0];
            result.line = tmp[1].toInt();
            stringType = UNDEFINED;
        }
        else if(stringType == RETURN_VALUE_FLAG){
            result.returnValue = it.at(0);
            stringType = UNDEFINED;
        }
        else if(QString::compare(it, QString("Continuing.")) == 0){
            continue;
        }
        else if(QString::compare(it, QString("exited")) == 0){
            result.status = EXITED;
            stringType = UNDEFINED;
        }
        else if(QString::compare(it, QString("Breakpoint")) == 0){
            qDebug()<<"BreakPoint found";
            result.status = AT_BREAKPOINT;
            stringType = BREAKPOINT_FLAG;
        }
        else if(QString::compare(it, QString("at")) == 0){
            stringType = FILE_FLAG;
        }
        else if(QString::compare(it, QString("code")) == 0){
            stringType = RETURN_VALUE_FLAG;
        }
    }

    this->gdbResults = result;
    printResult(result);

    return;
}
