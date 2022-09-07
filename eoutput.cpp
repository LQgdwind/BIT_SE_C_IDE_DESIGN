#include "eoutput.h"


EOutPut::EOutPut(QWidget *parent) : QWidget(parent),layout(new QVBoxLayout),textBrowser(new QTextBrowser)
{
    this->setLayout(layout);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(this->textBrowser);
    this->initialEoutput();//初始化
    this->printForUiDesign();//用于测试
}

void EOutPut::printForUiDesign()
{
    //this->textBrowser->append(" Starting C:\\Users\\lx\\Desktop\\ide\\build-QEditor-Desktop_Qt_5_9_0_MinGW_32bit-Debug\\debug\\QEditor.exe...\n C:\\Users\\lx\\Desktop\\ide\\build-QEditor-Desktop_Qt_5_9_0_MinGW_32bit-Debug\\debug\\QEditor.exe exited with code 0");

}

void EOutPut::initialEoutput()
{
    QFont textFont;
    textFont.setFamily("Consolas");
    textFont.setPointSize(15);
    this->textBrowser->setFont(textFont);

}

