#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <qfiledialog>
#include <qmessagebox>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    layout(new QGridLayout),
    menubar(new EMenu),
    sidebar(new ESideBar),
    explorer(new Explorer),
    // build(new Build),
    editor(new Editor)
{
    ui->setupUi(this);
    menubar->editor=editor;
    menubar->explorer=explorer;
    menubar->mainwind=this;
    sidebar->appendActions(menubar);
    explorer->editor=editor;
    explorer->menu=menubar;
    this->build = new Build(menubar);
    connect(explorer,&Explorer::fileRenamed,editor->efilebar,&EfileBar::handleFileRenamed);
    connect(explorer,&Explorer::fileDeleted,editor->efilebar,&EfileBar::handleFileDeleted);
    connect(editor,&Editor::functionReferenceShouldChange,explorer,&Explorer::refreshFunctionReference);
    setupLayout();
}

void MainWindow::setupLayout()
{
    central =new QWidget(this);
    layout->addWidget(menubar,0,0,1,-1);
    layout->addWidget(sidebar,1,0,-1,1);
    layout->addWidget(explorer,1,1,-1,1);
    layout->addWidget(editor,1,2,-1,1);
    layout->setSpacing(0);
    layout->setMargin(0);
    central->setLayout(layout);
    this->setCentralWidget(central);
    menubar->setFixedHeight(30);
    menubar->setStyleSheet("background-color: rgb(60,60,60);color: rgb(160,160,160)");
    sidebar->setAutoFillBackground(true);
    sidebar->setFixedWidth(64);
    sidebar->setStyleSheet("background-color: rgb(51,51,51);color: rgb(160,160,160)");
    explorer->setFixedWidth(175);
    explorer->setStyleSheet("background-color: rgb(37,37,37);color: rgb(200,200,200)");
    editor->setStyleSheet("background-color: rgb(30,30,30);color: rgb(200,200,200)");
}

MainWindow::~MainWindow()
{
     delete ui;
}
