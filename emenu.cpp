#include "emenu.h"
#include <QInputDialog>

EMenu::EMenu(QWidget *parent) : QMenuBar(parent)
{

    fileMenu=new QMenu("File");
    this->addMenu(fileMenu);

    editMenu=new QMenu("Edit");
    this->addMenu(editMenu);

    runMenu=new QMenu("Run");
    this->addMenu(runMenu);

    helpMenu=new QMenu("Help");
    this->addMenu(helpMenu);

    openAct=new QAction("Open");
    openAct->setShortcut(tr("Ctrl+O"));
    fileMenu->addAction(openAct);

    openFolderAct=new QAction("Open Folder");
    openFolderAct->setShortcut(tr("Ctrl+Shift+O"));
    fileMenu->addAction(openFolderAct);

    saveAct=new QAction("Save");
    saveAct->setShortcut(tr("Ctrl+S"));
    fileMenu->addAction(saveAct);

    saveAsAct=new QAction("Save As");
    saveAsAct->setShortcut(tr("Ctrl+Shift+S"));
    fileMenu->addAction(saveAsAct);

    newFileAct=new QAction("New File");
    newFileAct->setShortcut(tr("Ctrl+N"));
    fileMenu->addAction(newFileAct);

    //Edit模块
    copyAct=new QAction("Copy");
    copyAct->setShortcut(tr("Ctrl+C"));
    editMenu->addAction(copyAct);

    pasteAct=new QAction("Paste");
    pasteAct->setShortcut(tr("Ctrl+V"));
    editMenu->addAction(pasteAct);

    cutAct=new QAction("Cut");
    cutAct->setShortcut(tr("Ctrl+X"));
    editMenu->addAction(cutAct);

    undoAct=new QAction("Undo");
    undoAct->setShortcut(tr("Ctrl+Z"));
    editMenu->addAction(undoAct);

    redoAct=new QAction("Redo");
    redoAct->setShortcut(tr("Ctrl+Y"));
    editMenu->addAction(redoAct);

    findAct=new QAction("Find");
    findAct->setShortcut(tr("Ctrl+F"));
    editMenu->addAction(findAct);

    replaceAct=new QAction("Replace");
    replaceAct->setShortcut(tr("Ctrl+H"));
    editMenu->addAction(replaceAct);

    beautifyAct=new QAction("Beautify");
    beautifyAct->setShortcut(tr("Ctrl+Alt+L"));
    editMenu->addAction(beautifyAct);

    connect(openAct,SIGNAL(triggered()),this,SLOT(on_open_click()));
    connect(openFolderAct,SIGNAL(triggered()),this,SLOT(on_open_folder_click()));
    connect(saveAct,SIGNAL(triggered()),this,SLOT(on_save_click()));
    connect(saveAsAct,SIGNAL(triggered()),this,SLOT(on_save_as_click()));
    connect(newFileAct,SIGNAL(triggered()),this,SLOT(on_new_file_click()));
    connect(copyAct,SIGNAL(triggered()),this,SLOT(on_copy_click()));
    connect(cutAct,SIGNAL(triggered()),this,SLOT(on_cut_click()));
    connect(pasteAct,SIGNAL(triggered()),this,SLOT(on_paste_click()));
    connect(undoAct,SIGNAL(triggered()),this,SLOT(on_undo_click()));
    connect(redoAct,SIGNAL(triggered()),this,SLOT(on_redo_click()));
    connect(findAct,SIGNAL(triggered()),this,SLOT(on_find_click()));
    connect(replaceAct,SIGNAL(triggered()),this,SLOT(on_replace_click()));
    connect(beautifyAct,SIGNAL(triggered()),this,SLOT(on_beautify_click()));
    runAct = new QAction("Run");
    compileAct = new QAction("Compile");
    runAct->setShortcut(tr("Ctrl+R"));
    compileAct->setShortcut(tr("Ctrl+F5"));
    runMenu->addAction(compileAct);
    runMenu->addAction(runAct);
    connect(this->runAct,SIGNAL(triggered()),this,SLOT(on_run_click()));
    connect(this->compileAct,SIGNAL(triggered()),this,SLOT(on_compile_click()));
}

bool EMenu::isQualified()
{
    return editor->edit!=editor->OriginalEdit;
}



void EMenu::on_open_click()
{
    QString file_path=QFileDialog::getOpenFileName(this, tr("Open File"),"C://",tr("C Files(*.c *.h *.txt)"));
    if(file_path.isEmpty())return;
    QFileInfo info=QFileInfo(file_path);
    explorer->addRootDir(info.dir());
    QList<QTreeWidgetItem*> results=explorer->fileTree->findItems(info.fileName(),Qt::MatchExactly|Qt::MatchRecursive);
    for(auto &result:results){
        QString ans=result->data(0,Qt::UserRole).toString();
        if(ans==info.absoluteFilePath()){
            result->setSelected(true);
            emit explorer->fileTree->itemDoubleClicked(result,0);
            break;
        }
    }
}

void EMenu::on_open_folder_click()
{
    QString selectedDir = QFileDialog::getExistingDirectory();
    if(selectedDir.isEmpty())return;
    QDir dir=QDir(selectedDir);
    explorer->addRootDir(dir);
    QList<QTreeWidgetItem*> results=explorer->fileTree->findItems(dir.dirName(),Qt::MatchExactly|Qt::MatchRecursive);
    for(auto &result:results){
        QString ans=result->data(0,Qt::UserRole).toString();
        if(ans==selectedDir){
            result->setSelected(true);
            break;
        }
    }

}

void EMenu::on_save_click()
{
    if(isQualified()){
        QString curEditing=editor->efilebar->curEditing;
        editor->edit->saveToFile(curEditing);
        editor->efilebar->openedFiles.value(curEditing).label->updateCommitStatus(false);
    }
}

void EMenu::on_new_file_click()
{
    QTreeWidgetItem* ans=explorer->findSelectedDir();
    if(!ans){
        QMessageBox::information(parentWidget(),tr("info"),tr("Please open and select a folder to create a new file"));
        return;
    }
    bool ok;
    QString text = QInputDialog::getText(parentWidget(),"filename","filename", QLineEdit::Normal,"", &ok);
    if(ok){
        QString npath=ans->data(0,Qt::UserRole).toString()+"/"+text;
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
        ans->insertChild(0,nitem);
        ans->setSelected(false);
        nitem->setSelected(true);
        emit explorer->fileTree->itemDoubleClicked(nitem,0);
    }
}


void EMenu::on_save_as_click()
{
    if(isQualified()){
        QString curPath=QDir::currentPath();
        QString dlgTitle="Save as...";
        QString filter="*.c;;*.h;;*.txt";
        QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
        if (aFileName.isEmpty())
            return;
        editor->edit->saveToFile(aFileName);
    }
}

void EMenu::on_copy_click()
{
    clipboard = QApplication::clipboard();
    QString txt = editor->edit->textCursor().selectedText();
    if(txt == "")
        clipboard->setText("");
    else
        clipboard->setText(txt);
}

void EMenu::on_paste_click()
{
    clipboard = QApplication::clipboard();
    QString txt = clipboard->text();
    editor->edit->textCursor().insertText(txt);
}

void EMenu::on_cut_click()
{
    clipboard = QApplication::clipboard();
    QString txt = editor->edit->textCursor().selectedText();
    if(txt == "")
        clipboard->setText("");
    else
        clipboard->setText(txt);
    editor->edit->textCursor().removeSelectedText();
}

void EMenu::on_undo_click()
{
    editor->edit->undo();
}
void EMenu::on_redo_click()
{
    editor->edit->redo();
}

void EMenu::on_find_click()
{
   finddialog = new FindDialog(this,editor->edit);
   finddialog->show();
}

void EMenu::on_replace_click()
{
    replacedialog = new ReplaceDialog(this,editor->edit);
    replacedialog->show();
}

void EMenu::on_beautify_click()
{

}

void EMenu::on_compile_click()
{
    emit compile_signal();
    //by zlq 8.27 10:04 解耦，具体实现放在build.cpp
}

void EMenu::on_run_click()
{
    emit run_signal();
    //by zlq 8.27 10:04 解耦，具体实现放在build.cpp
}
