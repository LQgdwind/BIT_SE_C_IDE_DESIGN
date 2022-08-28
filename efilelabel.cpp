#include "efilelabel.h"

EFileLabel::EFileLabel(QString filePath, QTextEdit *edit,QWidget *parent) :
    QWidget(parent),
    filePath(filePath),
    edit(edit),
    openFile(new QPushButton),
    exitFile(new QPushButton),
    layout(new QHBoxLayout)
{
    setupLayout();
    connect(openFile,SIGNAL(clicked()),this,SLOT(on_open_file_click()));
    connect(exitFile,SIGNAL(clicked()),this,SLOT(on_close_file_click()));
}

EFileLabel::setupLayout()
{
    layout->addWidget(openFile);
    layout->addWidget(exitFile);
    layout->setSpacing(0);
    layout->setMargin(0);
    this->setMaximumWidth(100);
    this->setLayout(layout);
    exitFile->setText("X");
    exitFile->setMaximumWidth(20);
    openFile->setText(QFileInfo(filePath).fileName());
    openFile->setMaximumWidth(80);
}

void EFileLabel::on_open_file_click()
{
    QFile file{filePath};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    QTextStream in(&file);
    QString context{""};
    while(!in.atEnd()){
        context.append(in.readLine());
    }
    edit->setText(context);
}

void EFileLabel::on_close_file_click()
{

}
