#include "editor.h"


Editor::Editor(QWidget *parent) : QWidget(parent),layout(new QVBoxLayout),efilebar(new EfileBar),edit(new QTextEdit),eoutputlabel(new QLabel),eoutput(new EOutPut)
{
    setupLayout();
    efilebar->edit=edit;
}

void Editor::setupLayout()
{
    layout->addWidget(efilebar);
    layout->addWidget(edit);
    layout->addWidget(eoutputlabel);
    layout->addWidget(eoutput);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    efilebar->setFixedHeight(25);
    //efilebar->setStyleSheet("background-color: rgb(128,128,128)");
    //this->setStyleSheet("background-color: rgb(150,150,150)");
    //这两行的css不要了！22.8.27 9:26 am by zlq
    QFont textFont;
    textFont.setFamily("Consolas");
    textFont.setPointSize(15);
    this->edit->setFont(textFont);
    this->edit->setStyleSheet("color: black");

    eoutputlabel->setFixedHeight(25);
    eoutputlabel->setText(" Output");
    textFont.setPointSize(12);
    eoutputlabel->setFont(textFont);
    eoutput->setFixedHeight(150);

}
