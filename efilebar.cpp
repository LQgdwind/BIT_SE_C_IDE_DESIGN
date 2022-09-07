#include "efilebar.h"


EfileBar::EfileBar(QWidget *parent) : QWidget(parent),layout(new QHBoxLayout)
{
    this->setLayout(layout);
    layout->setSpacing(1);
    layout->setMargin(0);
    layout->setDirection(QBoxLayout::RightToLeft);
    layout->addWidget(new QLabel,1);
}

void EfileBar::open_file(QString file_path)
{
    if(openedFiles.contains(file_path)){
        emit openedFiles.value(file_path).label->on_open_file_click();
        return;
    }
    QFile file{file_path};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    QTextStream in(&file);
    QString context{""};
    while(!in.atEnd()){
        context.append(in.readLine());
        context.append("\n");
    }
    EFileLabel *filelab=new EFileLabel(file_path);
    filelab->setParent(this);
    EcodeEditor *edit=new EcodeEditor();
    edit->setPlainText(context);
    layout->addWidget(filelab);
    openedFiles.insert(file_path,EFileInfo(filelab,edit));
    connect(edit,&EcodeEditor::textChanged,filelab,&EFileLabel::handleUncommitChange);
    connect(edit,&EcodeEditor::textChanged,this,&EfileBar::shouldUpdateRef);
    connect(filelab,&EFileLabel::closeClicked,this,&EfileBar::deleteLabel);
    connect(filelab,&EFileLabel::openClicked,this,&EfileBar::showLabel);
    filelab->on_open_file_click();
}

void EfileBar::showLabel(QString name)
{
    if(openedFiles.contains(curEditing))openedFiles.value(curEditing).label->setIsChosen(false);
    curEditing=name;
    openedFiles.value(curEditing).label->setIsChosen(true);
    emit updateEdit(openedFiles.value(name).edit);
}

void EfileBar::deleteLabel(QString name)
{
    EFileLabel *aimLab=openedFiles.value(name).label;
    EcodeEditor *aimEdit=openedFiles.value(name).edit;
    if(aimLab->getChangeUnCommit()){
        QMessageBox::StandardButton res=QMessageBox::question(parentWidget(),tr("unsaved file"),tr("Whether you want to save an unsaved file?"));
        if(res==QMessageBox::Yes)aimEdit->saveToFile(name);
    }
    if(name==curEditing){
        bool hasNext{false};
        for(auto& child:children()){
            EFileLabel *lab=qobject_cast<EFileLabel*>(child);
            if((!lab)||(lab==aimLab))continue;
            hasNext=true;
            lab->on_open_file_click();
            break;
        }
        if(!hasNext){
            updateEdit(nullptr);
        }
    }
    openedFiles.remove(name);
    aimLab->deleteLater();
    aimEdit->deleteLater();
}

void EfileBar::handleFileRenamed(QString oldName, QString newName)
{
    if(!openedFiles.contains(oldName))return;
    EFileLabel *aimLab=openedFiles.value(oldName).label;
    aimLab->setFilePath(newName);
    if(oldName==curEditing)curEditing=newName;
    openedFiles.insert(newName,openedFiles.value(oldName));
    openedFiles.remove(oldName);
}

void EfileBar::handleFileDeleted(QString name)
{
    if(!openedFiles.contains(name))return;
    EFileLabel *aimLab=openedFiles.value(name).label;
    EcodeEditor *aimEdit=openedFiles.value(name).edit;
    if(name==curEditing){
        bool hasNext{false};
        for(auto& child:children()){
            EFileLabel *lab=qobject_cast<EFileLabel*>(child);
            if((!lab)||(lab==aimLab))continue;
            hasNext=true;
            lab->on_open_file_click();
            break;
        }
        if(!hasNext){
            updateEdit(nullptr);
        }
    }
    openedFiles.remove(name);
    aimLab->deleteLater();
    aimEdit->deleteLater();
}
