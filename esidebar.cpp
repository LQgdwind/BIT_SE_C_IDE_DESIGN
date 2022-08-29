#include "esidebar.h"


ESideBar::ESideBar(QWidget *parent) : QWidget(parent)
{

    //explorer_icon
    this->exploreBtn = new QPushButton(this);
    exploreBtn->setMaximumSize(64,64);
    exploreBtn->setMinimumSize(64,64);
    QIcon con1(":/images/explorer_icon.png");
    exploreBtn->setIcon(con1);
    exploreBtn->setIconSize(QSize(50,50));
    exploreBtn->setAutoFillBackground(true);

    //search_icon
    this->searchBtn = new QPushButton(this);
    searchBtn->setMaximumSize(64,64);
    searchBtn->setMinimumSize(64,64);
    QIcon con2(":/images/search_icon.png");
    searchBtn->setIcon(con2);
    searchBtn->setIconSize(QSize(50,50));
    searchBtn->setAutoFillBackground(true);
    searchBtn->setGeometry(0,64,64,64);

    //run_icon
    this->runBtn = new QPushButton(this);
    runBtn->setMaximumSize(64,64);
    runBtn->setMinimumSize(64,64);
    QIcon con3(":/images/run_icon.png");
    runBtn->setIcon(con3);
    runBtn->setIconSize(QSize(50,50));
    runBtn->setAutoFillBackground(true);
    runBtn->setGeometry(0,128,64,64);

    //compile_icon
    this->compileBtn = new QPushButton(this);
    compileBtn->setMaximumSize(64,64);
    compileBtn->setMinimumSize(64,64);
    QIcon con4(":/images/compile_icon.png");
    compileBtn->setIcon(con4);
    compileBtn->setIconSize(QSize(50,50));
    compileBtn->setAutoFillBackground(true);
    compileBtn->setGeometry(0,192,64,64);

//    待定的槽
//    connect(exploreBtn,SIGNAL(clicked(bool)), ,SLOT());
//    connect(searchBtnBtn,SIGNAL(clicked(bool)), ,SLOT());
//    connect(runBtn,SIGNAL(clicked(bool)), ,SLOT());
//    connect(compileBtn,SIGNAL(clicked(bool)), ,SLOT());
}
