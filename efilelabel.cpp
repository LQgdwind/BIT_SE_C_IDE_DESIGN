#include "efilelabel.h"

EFileLabel::EFileLabel(QString filePath,QWidget *parent) :
    QWidget(parent),
    filePath(filePath),
    fileName(QFileInfo(filePath).fileName()),
    openFile(new QPushButton),
    exitFile(new QPushButton),
    layout(new QHBoxLayout)
{
    setupLayout();
    connect(openFile,&QPushButton::clicked,this,&EFileLabel::on_open_file_click);
    connect(exitFile,&QPushButton::clicked,this,&EFileLabel::on_close_file_click);
}

void EFileLabel::updateLabelName()
{
    QString newName=fileName;
    if(changeUnCommit)newName+="*";
    openFile->setText(newName);
}

void EFileLabel::updateCommitStatus(bool status)
{
    changeUnCommit=status;
    updateLabelName();
}

EFileLabel::setupLayout()
{
    layout->addWidget(openFile);
    layout->addWidget(exitFile);
    layout->setSpacing(0);
    layout->setMargin(0);
    this->setMaximumWidth(250);
    this->setLayout(layout);
    exitFile->setText("X");
    exitFile->setMaximumWidth(20);
    updateLabelName();
    //openFile->setMaximumWidth(80);
}

void EFileLabel::setIsChosen(bool value)
{
    isChosen = value;
    if(isChosen)this->setStyleSheet("background-color:gray");
    else this->setStyleSheet("background-color:white");
}

bool EFileLabel::getIsChosen() const
{
    return isChosen;
}

bool EFileLabel::getChangeUnCommit() const
{
    return changeUnCommit;
}

void EFileLabel::handleUncommitChange()
{
    updateCommitStatus(true);
}

void EFileLabel::on_open_file_click()
{
    isChosen=true;
    emit openClicked(filePath);
}

void EFileLabel::on_close_file_click()
{
    emit closeClicked(filePath);
}
