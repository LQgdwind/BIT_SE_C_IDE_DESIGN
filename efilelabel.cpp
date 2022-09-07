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
    //openFile->setStyleSheet("background-color: rgb(30,30,30);color: rgb(200,200,200)");//文件名
    //exitFile->setStyleSheet("background-color: rgb(30,30,30);color: rgb(200,200,200)");//退出文件
    updateLabelName();
    //openFile->setMaximumWidth(80);
}

QString EFileLabel::getFilePath() const
{
    return filePath;
}

void EFileLabel::setFilePath(const QString &value)
{
    filePath = value;
    fileName=QFileInfo(filePath).fileName();
    updateLabelName();
}

void EFileLabel::setIsChosen(bool value)
{
    isChosen = value;
//    if(isChosen)this->setStyleSheet("background-color: rgb(30,30,30);color: rgb(200,200,200)");//选择
//    else this->setStyleSheet("background-color: rgb(45,45,45);color: rgb(160,160,160)");//未选择
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
