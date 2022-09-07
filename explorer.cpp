#include "explorer.h"
#include "emenu.h"
#include <QInputDialog>

Explorer::Explorer(QWidget *parent) : QWidget(parent),header(new QLabel("Explorer")),layout(new QVBoxLayout),fileTree(new QTreeWidget),functionTree(new QListWidget)
{
    setupLayout();
    connect(fileTree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(open_in_editor(QTreeWidgetItem*,int)));
    connect(functionTree,&QListWidget::itemClicked,this,&Explorer::handleFunctionRefClicked);
    fileTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(fileTree,&QTreeWidget::customContextMenuRequested,this,&Explorer::handleMenuRequested);
}

void Explorer::addRootDir(QDir dir)
{
    QTreeWidgetItem *root=new QTreeWidgetItem();
    root->setText(0,dir.dirName());
    root->setData(0,Qt::UserRole,dir.absolutePath());
    QFileInfoList children=dir.entryInfoList();
    for(auto& child:children){
        QString childname=child.fileName();
        if(childname=="."||childname=="..")continue;
        addNode(child,root);
    }
    fileTree->addTopLevelItem(root);
    root->setExpanded(true);
}

QTreeWidgetItem* Explorer::findSelectedDir()
{
    QTreeWidgetItem *ans=nullptr;
    QList<QTreeWidgetItem *> candidates=fileTree->selectedItems();
    if(candidates.size()>0){
        QString name=candidates.value(0)->data(0,Qt::UserRole).toString();
        QFileInfo file{name};
        if(file.exists()&&file.isDir())ans=candidates.value(0);
    }
    return ans;
}

void Explorer::addNode(QFileInfo &info, QTreeWidgetItem *root)
{
    QTreeWidgetItem *child=new QTreeWidgetItem();
    QString path=info.absoluteFilePath();
    if(info.isDir()){
        QDir cur=QDir(path);
        child->setText(0,cur.dirName());
        child->setData(0,Qt::UserRole,path);
        QFileInfoList children=cur.entryInfoList();
        for(auto& achild:children){
            QString childname=achild.fileName();
            if(childname=="."||childname=="..")continue;
            addNode(achild,child);
        }
    }else{
        child->setText(0,info.fileName());
        child->setData(0,Qt::UserRole,path);
    }
    root->addChild(child);
}

void Explorer::setupLayout()
{
    //this->setStyleSheet("background-color: rgb(169,169,169)");//侧栏
    layout->addWidget(header);
    layout->addWidget(fileTree,6);
    layout->addWidget(functionTree,4);
    layout->setMargin(0);
    layout->setSpacing(0);
    QFont font=QFont("Consolas", 10, 75);
    header->alignment();
    header->setFont(font);
    header->setAlignment(Qt::AlignCenter);
    //header->setStyleSheet("background-color: rgb(128,128,128)");//侧栏上方
    header->setFixedHeight(25);
    fileTree->setHeaderHidden(true);    
    this->setLayout(layout);
}

void Explorer::deleteItem(QTreeWidgetItem *item)
{
    QString filePath=item->data(0,Qt::UserRole).toString();
    if(QFileInfo(filePath).isDir()){
        for(int i=0;i<item->childCount();i++){
            QTreeWidgetItem *child=item->child(i);
            deleteItem(child);
        }
        QDir(filePath).rmpath(filePath);
    }else{
        emit fileDeleted(filePath);
        QFile(filePath).remove();
    }
}

void Explorer::open_in_editor(QTreeWidgetItem *item, int column)
{
    QString file_path=item->data(0,Qt::UserRole).toString();
    if(!QFileInfo(file_path).isDir())editor->efilebar->open_file(file_path);
}

void Explorer::handleMenuRequested(QPoint pos)
{
    QTreeWidgetItem *clickedItem=fileTree->itemAt(pos);
    QMenu fileMenu(this);
    if(!clickedItem){
        fileMenu.addAction(menu->openAct);
        fileMenu.addAction(menu->openFolderAct);
        QAction *clearAct = new QAction(tr("Close All"));
        connect(clearAct,&QAction::triggered,this, [&](){
           fileTree->clear();
        });
        fileMenu.addAction(clearAct);
    }else{
        QString filePath=clickedItem->data(0,Qt::UserRole).toString();
        QFileInfo info{filePath};
        if(info.isDir()){
            QDir cdir{filePath};
            QAction *renameFolderAct = new QAction("Rename");
            QAction *removeFolderAct = new QAction("Remove");
            QAction *deleteFolderAct= new QAction("Delete");
            QAction *createFileAct=new QAction("Create File");
            QAction *createFolderAct=new QAction("Create Folder");
            connect(renameFolderAct,&QAction::triggered,this,[&](){
                bool ok;
                QString text = QInputDialog::getText(parentWidget(),"Rename Folder","foldername", QLineEdit::Normal,"", &ok);
                if(ok){
                    QDir pdir{filePath};
                    pdir.cdUp();
                    QString npath=pdir.absolutePath()+"/"+text;
                    QDir ndir{npath};
                    if(ndir.exists()){
                        QMessageBox::information(parentWidget(),tr("info"),tr("The new folder name exists in the current directory"));
                        return;
                    }
                    cdir.rename(filePath,npath);
                    clickedItem->setText(0,text);
                    clickedItem->setData(0,Qt::UserRole,npath);
                }
            });
            connect(removeFolderAct,&QAction::triggered,this,[&](){
                for(int i=0;i<fileTree->topLevelItemCount();i++){
                    QTreeWidgetItem *cmp=fileTree->topLevelItem(i);
                    if(cmp==clickedItem){
                        fileTree->takeTopLevelItem(i);
                        delete clickedItem;
                        return;
                    }
                    QMessageBox::information(parentWidget(),tr("info"),tr("you can only remove toplevel directory"));
                }
            });
            connect(deleteFolderAct,&QAction::triggered,this,[&](){
                QMessageBox::StandardButton btn=QMessageBox::question(parentWidget(),tr("Irreversible Choice"),tr("Whether you want to delete the folder and all its contents?"));
                if(btn==QMessageBox::Yes){
                    deleteItem(clickedItem);
                    delete  clickedItem;
                }
            });
            connect(createFileAct,&QAction::triggered,this,[&](){
                bool ok;
                QString text = QInputDialog::getText(parentWidget(),"filename","filename", QLineEdit::Normal,"", &ok);
                if(ok){
                    QString npath=filePath+"/"+text;
                    QFile nfile{npath};
                    if(nfile.exists()){
                        QMessageBox::information(parentWidget(),tr("info"),tr("The file name exists in the current directory"));
                        return;
                    }
                    nfile.open(QIODevice::WriteOnly);
                    nfile.close();
                    QTreeWidgetItem* nitem=new QTreeWidgetItem;
                    nitem->setText(0,text);
                    nitem->setData(0,Qt::UserRole,npath);
                    if(!clickedItem->isExpanded())clickedItem->setExpanded(true);
                    clickedItem->insertChild(0,nitem);
                    clickedItem->setSelected(false);
                    nitem->setSelected(true);
                    emit fileTree->itemDoubleClicked(nitem,0);
            }});
            connect(createFolderAct,&QAction::triggered,this,[&](){
                bool ok;
                QString text = QInputDialog::getText(parentWidget(),"foldername","foldername", QLineEdit::Normal,"", &ok);
                if(ok){
                    QString npath=filePath+"/"+text;
                    QDir ndir{npath};
                    if(ndir.exists()){
                        QMessageBox::information(parentWidget(),tr("info"),tr("The folder name exists in the current directory"));
                        return;
                    }
                    cdir.mkdir(npath);
                    QTreeWidgetItem* nitem=new QTreeWidgetItem;
                    nitem->setText(0,text);
                    nitem->setData(0,Qt::UserRole,npath);
                    clickedItem->addChild(nitem);
                    clickedItem->setSelected(false);
                    nitem->setSelected(true);
                    emit fileTree->itemDoubleClicked(nitem,0);
                }
            });
            fileMenu.addAction(removeFolderAct);
            fileMenu.addAction(createFileAct);
            fileMenu.addAction(createFolderAct);
            fileMenu.addAction(renameFolderAct);
            fileMenu.addAction(deleteFolderAct);
        }else{
            QAction *renameFileAct = new QAction("Rename");
            QAction *deleteFileAct= new QAction("Delete");
            connect(renameFileAct,&QAction::triggered,this,[&](){
                QFile file{filePath};
                bool ok;
                QString text = QInputDialog::getText(parentWidget(),"Rename File","fileName", QLineEdit::Normal,"", &ok);
                if(ok){
                    QFile file{filePath};
                    QString npath=QFileInfo(filePath).dir().absolutePath()+"/"+text;
                    QFile nfile{npath};
                    if(nfile.exists()){
                        QMessageBox::information(parentWidget(),tr("info"),tr("The new file name exists in the current directory"));
                        return;
                    }
                    file.rename(npath);
                    clickedItem->setText(0,text);
                    clickedItem->setData(0,Qt::UserRole,npath);
                    emit fileRenamed(filePath,npath);
                }
            });
            connect(deleteFileAct,&QAction::triggered,this,[&](){
                QMessageBox::StandardButton btn=QMessageBox::question(parentWidget(),tr("Irreversible Choice"),tr("Whether you want to delete the file"));
                if(btn==QMessageBox::Yes){
                    clickedItem->parent()->removeChild(clickedItem);
                    delete  clickedItem;
                    QFile(filePath).remove();
                    emit fileDeleted(filePath);
                }
            });
            fileMenu.addAction(renameFileAct);
            fileMenu.addAction(deleteFileAct);
        }
    }
    fileMenu.exec(fileTree->mapToGlobal(pos));
}

void Explorer::refreshFunctionReference(EcodeEditor *curEditor)
{
    functionTree->clear();
    edit=curEditor;
    curs.clear();
    QTextDocument *doc=edit->document();
    QRegularExpression re(R"((static\s*){0,1}\w{1,}\s{1,}\w{1,}\s*\([\s\w\*,]*\))");
    QTextCursor before{QTextCursor(doc->begin())};
    QTextCursor after=doc->find(re);
    while(!after.isNull()){
        curs.append(after);
        before=after;
        QListWidgetItem *item=new QListWidgetItem;
        QString syb=after.selectedText()+";";
        item->setText(syb);
        item->setData(Qt::UserRole,curs.size()-1);
        functionTree->addItem(item);
        after=doc->find(re,before);
    }
}

void Explorer::handleFunctionRefClicked(QListWidgetItem *item)
{
    QTextCursor clickedCurs=curs.value(item->data(Qt::UserRole).toInt());
    edit->setTextCursor(clickedCurs);
}
