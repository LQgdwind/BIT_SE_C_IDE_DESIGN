#include "emenu.h"
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QDesktopServices>
#include "etheme.h"
#include "mainwindow.h"
#include "debuggerpage.h"

EMenu::EMenu(QWidget *parent) : QMenuBar(parent)
{
    fileMenu=new QMenu("File");
    fileMenu->setPalette(QColor(60,60,60));
    this->addMenu(fileMenu);

    editMenu=new QMenu("Edit");
    editMenu->setPalette(QColor(60,60,60));
    this->addMenu(editMenu);

    runMenu=new QMenu("Run");
    runMenu->setPalette(QColor(60,60,60));
    this->addMenu(runMenu);

    appearanceMenu=new QMenu("Appearance");
    appearanceMenu->setPalette(QColor(60,60,60));
    this->addMenu(appearanceMenu);

    themeMenu=appearanceMenu->addMenu("Theme");
    themeMenu->setPalette(QColor(60,60,60));

    helpMenu=new QMenu("Help");
    helpMenu->setPalette(QColor(60,60,60));
    this->addMenu(helpMenu);

    fontAct=new QAction("Font");
    fontAct->setShortcut(tr("Ctrl+Shift+F"));
    appearanceMenu->addAction(fontAct);

    colorAct=new QAction("Color");
    colorAct->setShortcut(tr("Ctrl+Shift+C"));
    appearanceMenu->addAction(colorAct);

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

    newFolderAct=new QAction("New Folder");
    newFolderAct->setShortcut(tr("Ctrl+Shift+N"));
    fileMenu->addAction(newFolderAct);

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

    allfoldAct=new QAction("Allfold");
    allfoldAct->setShortcut(tr("Ctrl+Q"));
    editMenu->addAction(allfoldAct);

    allunfoldAct=new QAction("Allunfold");
    allunfoldAct->setShortcut(tr("Ctrl+Shift+Q"));
    editMenu->addAction(allunfoldAct);

    learnAct=new QAction("Learn");
    learnAct->setShortcut(tr("Ctrl+L"));
    helpMenu->addAction(learnAct);

    darkAct=new QAction("dark");
    themeMenu->addAction(darkAct);

    whiteAct=new QAction("white");
    themeMenu->addAction(whiteAct);

    blueAct=new QAction("quite light");
    themeMenu->addAction(blueAct);

    connect(allfoldAct,&QAction::triggered,this,&EMenu::on_allfold_click);
    connect(allunfoldAct,&QAction::triggered,this,&EMenu::on_allunfold_click);
    connect(darkAct,&QAction::triggered,this,&EMenu::on_dark_click);
    connect(whiteAct,&QAction::triggered,this,&EMenu::on_white_click);
    connect(blueAct,&QAction::triggered,this,&EMenu::on_blue_click);
    connect(fontAct,&QAction::triggered,this,&EMenu::on_font_click);
    connect(colorAct,&QAction::triggered,this,&EMenu::on_color_click);
    connect(learnAct,SIGNAL(triggered()),this,SLOT(on_learn_click()));
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
    runAct = new QAction("Run");
    compileAct = new QAction("Compile");
    runAct->setShortcut(tr("Ctrl+R"));
    compileAct->setShortcut(tr("Ctrl+F5"));
    runMenu->addAction(compileAct);
    runMenu->addAction(runAct);
    debugAct = new QAction("debug");
    debugAct->setShortcut(tr("Ctrl+shift+F5"));
    runMenu->addAction(debugAct);
    connect(this->runAct,SIGNAL(triggered()),this,SLOT(on_run_click()));
    connect(this->compileAct,SIGNAL(triggered()),this,SLOT(on_compile_click()));
    connect(this->debugAct,SIGNAL(triggered()),this,SLOT(on_debug_click()));
    connect(newFolderAct,&QAction::triggered,this,&EMenu::on_new_folder_click);
}

bool EMenu::isQualified()
{
    return editor->edit!=editor->OriginalEdit;
}

void EMenu::on_font_click()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                    &ok,editor->getCurFont(), this);
    if (ok) {
        editor->setCurFont(font);
    }
}

void EMenu::on_color_click()
{
    QColor color=QColorDialog::getColor(editor->getCurColor(),this);
    if(color.isValid()){
        editor->setCurColor(color);
    }
}

void EMenu::on_dark_click()
{
    ETheme::curTheme=ETheme::black;
    ETheme::updateColorGlobally(mainwind);
}

void EMenu::on_white_click()
{
    ETheme::curTheme=ETheme::white;
    ETheme::updateColorGlobally(mainwind);
}

void EMenu::on_blue_click()
{
    ETheme::curTheme=ETheme::blue;
    ETheme::updateColorGlobally(mainwind);
}

void EMenu::on_allfold_click()
{
    editor->edit->allhideline(true);
    editor->edit->allhidenoteline(true);
}

void EMenu::on_allunfold_click()
{
    editor->edit->allhideline(false);
    editor->edit->allhidenoteline(false);
}

void EMenu::on_debug_click()
{
    debuggerPage *newPage = new debuggerPage();
    newPage->initializeDebugger(this->buildPath + "/debug");
    newPage->show();
    qDebug("debug");
}

void EMenu::on_learn_click()
{
    QPushButton *yesbtn = new QPushButton(QString::fromLocal8Bit("Yes"));
    QPushButton *nobtn = new QPushButton(QString::fromLocal8Bit("No"));
    QMessageBox msg(this);
    msg.setWindowTitle("Find");
    msg.setText("Are you sure to open the C Programming learning website?");
    msg.setIcon(QMessageBox::Information);
    msg.addButton(yesbtn, QMessageBox::AcceptRole);
    msg.addButton(nobtn, QMessageBox::RejectRole);
    msg.show();

    msg.exec();//阻塞等待用户输入
    if (msg.clickedButton()==yesbtn)//点击了Yes按钮
    {
        QDesktopServices::openUrl(QUrl(QString("https://www.runoob.com/cprogramming/c-tutorial.html")));
    }
    else{

    }
}

void EMenu::on_open_click()
{
    QString file_path=QFileDialog::getOpenFileName(this, tr("Open File"),"C://",tr("C Files(*.c *.h *.txt)"));
    if(file_path.isEmpty())return;
    QFileInfo info=QFileInfo(file_path);

    QList<QTreeWidgetItem*> results=explorer->fileTree->findItems(info.fileName(),Qt::MatchExactly|Qt::MatchRecursive);
    if(results.size()==0){
        explorer->addRootDir(info.dir());
        results=explorer->fileTree->findItems(info.fileName(),Qt::MatchExactly|Qt::MatchRecursive);
    }
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
    emit selected_folder(selectedDir);
    QList<QTreeWidgetItem*> results=explorer->fileTree->findItems(dir.dirName(),Qt::MatchExactly|Qt::MatchRecursive);
    if(results.size()==0){
        explorer->addRootDir(dir);
        results=explorer->fileTree->findItems(dir.dirName(),Qt::MatchExactly|Qt::MatchRecursive);
    }
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
        if(!ans->isExpanded())ans->setExpanded(true);
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

void EMenu::on_new_folder_click()
{
    QTreeWidgetItem* ans=explorer->findSelectedDir();
    if(!ans){
        QMessageBox::information(parentWidget(),tr("info"),tr("Please open and select a folder to create a new folder"));
        return;
    }
    bool ok;
    QString text = QInputDialog::getText(parentWidget(),"foldername","foldername", QLineEdit::Normal,"", &ok);
    if(ok){
        QString npath=ans->data(0,Qt::UserRole).toString()+"/"+text;
        QDir ndir{npath};
        if(ndir.exists()){
            QMessageBox::information(parentWidget(),tr("info"),tr("The folder name exists in the current directory"));
            return;
        }
        QDir pdir{ans->data(0,Qt::UserRole).toString()};
        pdir.mkdir(npath);
        QTreeWidgetItem* nitem=new QTreeWidgetItem;
        nitem->setText(0,text);
        nitem->setData(0,Qt::UserRole,npath);
        ans->addChild(nitem);
        ans->setSelected(false);
        nitem->setSelected(true);
        emit explorer->fileTree->itemDoubleClicked(nitem,0);
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
   if(isQualified())
   {
       finddialog = new FindDialog(this,editor->edit);
       finddialog->show();
   }
   else
   {
       QMessageBox::information(parentWidget(),tr("info"),tr("There are currently no editable files"));
       return;
   }

}

void EMenu::on_replace_click()
{
    if(isQualified())
    {
        replacedialog = new ReplaceDialog(this,editor->edit);
        replacedialog->show();
    }
    else
    {
        QMessageBox::information(parentWidget(),tr("info"),tr("There are currently no editable files"));
        return;
    }
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
