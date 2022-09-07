#include "editor.h"
#include <QPlainTextEdit>


Editor::Editor(QWidget *parent) : QWidget(parent),layout(new QVBoxLayout),efilebar(new EfileBar),OriginalEdit(new EcodeEditor),eoutputlabel(new QLabel),eoutput(new EOutPut)
{
    configureOriginalEdit();
    edit=OriginalEdit;
    connect(efilebar,&EfileBar::updateEdit,this,&Editor::handleUpdateEdit);
    connect(efilebar,&EfileBar::shouldUpdateRef,this,&Editor::updateFunctionRef);
    setupLayout();
}

QFont Editor::getCurFont() const
{
    return curFont;
}

void Editor::setCurFont(const QFont &value)
{
    curFont = value;
    configureFontAndColor();
}

QColor Editor::getCurColor() const
{
    return curColor;
}

void Editor::setCurColor(const QColor &value)
{
    curColor = value;
    configureFontAndColor();
}

void Editor::setupLayout()
{
    this->setLayout(layout);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(efilebar);
    efilebar->setFixedHeight(25);
    updateEditLayout();
    addTerminal();
}

void Editor::updateEditLayout()
{
    layout->addWidget(edit);
    QFont textFont;
    textFont.setFamily("Consolas");
    textFont.setPointSize(15);
    this->edit->setFont(textFont);
    //this->edit->setStyleSheet("background-color: rgb(70,70,70);color: balck");//编辑栏
}

void Editor::configureOriginalEdit()
{
    QString hint="\n\n\n\n\nOpen File  Ctrl+O\n"
                 "Open Folder  Ctrl+Shift+O\n"
                 "Create New File  Ctrl+N\n";
    OriginalEdit->setPlainText(hint);
    OriginalEdit->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter));
    OriginalEdit->setReadOnly(true);
}

void Editor::removeTerminal()
{
    layout->removeWidget(eoutputlabel);
    layout->removeWidget(eoutput);
}

void Editor::addTerminal()
{
    layout->addWidget(eoutputlabel);
    layout->addWidget(eoutput);
    eoutputlabel->setFixedHeight(25);
    eoutputlabel->setText(" Output");
    //eoutputlabel->setStyleSheet("background-color: rgb(200,200,200)");//output上侧
    QFont textFont;
    textFont.setFamily("Consolas");
    textFont.setPointSize(12);
    eoutputlabel->setFont(textFont);
    eoutput->setFixedHeight(150);
}

void Editor::configureFontAndColor()
{
    if(edit==OriginalEdit)return;
    QTextCharFormat fmt;
    fmt.setFont(curFont);
    fmt.setForeground(QBrush(curColor));
    int pos=edit->textCursor().position();
    edit->selectAll();
    edit->setCurrentCharFormat(fmt);
    QTextCursor textCurs=edit->textCursor();
    textCurs.clearSelection();
    textCurs.setPosition(pos);
    edit->setTextCursor(textCurs);
}

void Editor::handleUpdateEdit(EcodeEditor *newEdit)
{
    edit->setParent(nullptr);
    layout->removeWidget(edit);
    removeTerminal();
    edit=newEdit?newEdit:OriginalEdit;
    updateFunctionRef();
    configureFontAndColor();
    updateEditLayout();
    addTerminal();
}

void Editor::updateFunctionRef()
{
    emit functionReferenceShouldChange(edit);
}
