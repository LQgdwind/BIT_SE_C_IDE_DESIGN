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
    editor(new Editor)
{
    ui->setupUi(this);
    menubar->editor=editor;
    menubar->explorer=explorer;
    explorer->editor=editor;
    this->build = new Build(menubar);
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
    menubar->setStyleSheet("background-color: rgb(200,200,200)");
    sidebar->setAutoFillBackground(true);
    sidebar->setPalette(QPalette(Qt::white));
    sidebar->setFixedWidth(64);
    explorer->setFixedWidth(175);
}

MainWindow::~MainWindow()
{
     delete ui;
}
