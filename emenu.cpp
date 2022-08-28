#include "emenu.h"


EMenu::EMenu(QWidget *parent) : QMenuBar(parent),is_open(false),is_new_file(false)
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

    beautifyAct=new QAction("Beautify");
    beautifyAct->setShortcut(tr("Ctrl+Alt+L"));
    editMenu->addAction(beautifyAct);

    findAct=new QAction("Find");
    findAct->setShortcut(tr("Ctrl+F"));
    editMenu->addAction(findAct);

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
    this->runAct = new QAction("Run");
    this->compileAct = new QAction("Compile");
    this->runAct->setShortcut(tr("Ctrl+R"));
    this->compileAct->setShortcut(tr("Ctrl+F5"));
    this->runMenu->addAction(this->compileAct);
    this->runMenu->addAction(this->runAct);
    connect(this->runAct,SIGNAL(triggered()),this,SLOT(on_run_click()));
    connect(this->compileAct,SIGNAL(triggered()),this,SLOT(on_compile_click()));
}



void EMenu::on_open_click()
{
    QString file_path=QFileDialog::getOpenFileName(this, tr("Open File"),"C://",tr("C Files(*.c *.h)"));
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
    if(this->is_new_file)
    {
        if(this->editor->edit->toPlainText()=="")
        {
            QMessageBox::warning(this,"error","content can not be none!",QMessageBox::Ok);
        }
        else
        {
            QFileDialog fileDialog;
            QString str = fileDialog.getSaveFileName(this,"Open File","","Text File(*.txt)");
            if(str == "")
            {
                return;
            }
            QFile filename(str);
            if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"error","Open File Error!");
                return;
            }
            else
            {
                QTextStream textStream(&filename);
                QString str = this->editor->edit->toPlainText();
                textStream << str;
                this->file_string_current =str;
            }
            QMessageBox::information(this,"Save File","Save File Success",QMessageBox::Ok);
            filename.close();
            this->is_new_file = false;
            this->file_name_current = str;
        }
    }
    else
    {
        if(this->is_open)
        {
            QFile file(file_name_current);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"error","Open File Faile");
                return;
            }
            else
            {
                QTextStream textString(&file);
                QString str = this->editor->edit->toPlainText();
                textString << str;
                this->file_string_current = str;
                file.close();
            }
        }
        else
        {
            QMessageBox::warning(this,"Warning","Please new or open a file");
            return;
        }

    }
}

void EMenu::on_new_file_click()
{
    this->editor->edit->clear();
    this->editor->edit->setHidden(false);
    this->is_new_file = true;
    this->is_open = true;
}
void EMenu::on_save_as_click()
{
    QString curPath=QDir::currentPath();
    QString dlgTitle="Save as...";
    QString filter="h文件(*.h);;c文件(*.c);;文本文件(*.txt)";
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;
    saveTextByStream(aFileName);
    this->file_name_current = aFileName;
    this->is_new_file=false;
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
    clipboard = QApplication::clipboard();
    editor->edit->undo();
}
void EMenu::on_redo_click()
{
    clipboard = QApplication::clipboard();
    editor->edit->redo();
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

bool EMenu::openTextByStream(const QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.exists())
        return false;
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);
    this->file_string_current = aStream.readAll();
    this->editor->edit->setText(file_string_current);
    aFile.close();
    return  true;
}

bool EMenu::saveTextByStream(const QString &aFileName)
{
    QFile   aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream aStream(&aFile);
    QString str=editor->edit->toPlainText();
    aStream<<str;
    aFile.close();
    return  true;

}
