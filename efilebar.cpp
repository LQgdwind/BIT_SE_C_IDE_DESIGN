#include "efilebar.h"


EfileBar::EfileBar(QWidget *parent) : QWidget(parent),layout(new QHBoxLayout)
{
    this->setLayout(layout);

    layout->setSpacing(0);
    layout->setMargin(0);
    //EFileLabel filelab{"file_path",nullptr,this};
}

void EfileBar::open_file(QString file_path)
{
    for(auto& child:this->children()){
       EFileLabel *file=qobject_cast<EFileLabel*>(child);
       if(!file)continue;
       if(file->filePath==file_path){
           emit file->openFile->click();
           return;
       }
    }
    EFileLabel *filelab=new EFileLabel(file_path,edit,this);
    layout->addWidget(filelab);
    filelab->setStyleSheet("background-color: white");
    emit filelab->openFile->click();
}
