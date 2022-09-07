#include "etheme.h"
#include <QColor>
#include "mainwindow.h"

static int anscolor[3];

QString ETheme::getMenubarStyle()
{
    QString ans;
    switch (curTheme) {
    case THEME::black:
        ans="background-color: rgb(60,60,60);color: rgb(160,160,160)";
        break;
    case THEME::white:
        ans="background-color: rgb(221,221,221);color: rgb(75,75,75)";
        break;
    case THEME::blue:
        ans="background-color: rgb(196,183,215);color: rgb(130,130,130)";
        break;
    default:
        break;
    }
    return ans;
}

QString ETheme::getExplorerStyle()
{
    QString ans;
    switch (curTheme) {
    case THEME::black:
        ans="background-color: rgb(37,37,37);color: rgb(200,200,200)";
        break;
    case THEME::white:
        ans="background-color: rgb(243,243,243);color: rgb(130,130,130)";
        break;
    case THEME::blue:
        ans="background-color: rgb(242,242,242);color: rgb(168,168,168)";
        break;
    default:
        break;
    }
    return ans;
}

QString ETheme::getEditorStyle()
{
    QString ans;
    switch (curTheme) {
    case THEME::black:
        ans="background-color: rgb(30,30,30);color: rgb(200,200,200)";
        break;
    case THEME::white:
        ans="background-color: rgb(255,255,255);color: rgb(0,0,0)";
        break;
    case THEME::blue:
        ans="background-color: rgb(245,245,245);color: rgb(54,54,54)";
        break;
    default:
        break;
    }
    return ans;
}

void ETheme::setEditorFontColor(MainWindow *mainwidow)
{
    switch (curTheme) {
    case THEME::black:
        mainwidow->menubar->editor->setCurColor(QColor(200,200,200));
        break;
    case THEME::white:
        mainwidow->menubar->editor->setCurColor(QColor(54,54,54));
        break;
    default:
        break;
    }
}

int ETheme::getLineColorStyle()
{
    int ans;
    switch (curTheme) {
    case THEME::black:
        ans=30;
        break;
    case THEME::white:
        ans=255;
        break;
    case THEME::blue:
        ans=245;
        break;
    default:
        break;
    }
    return ans;
}

int ETheme::getCurrentLineColorStyle()
{
    int ans;
    switch (curTheme) {
    case THEME::black:
        ans=30;
        break;
    case THEME::white:
        ans=255;
        break;
    case THEME::blue:
        ans=245;
        break;
    default:
        break;
    }
    return ans;
}

int * ETheme::getFileMenuStyle()
{
    switch (curTheme) {
    case THEME::black:
        anscolor[0]=60;
        anscolor[1]=60;
        anscolor[2]=60;
        break;
    case THEME::white:
        anscolor[0]=221;
        anscolor[1]=221;
        anscolor[2]=221;
        break;
    case THEME::blue:
        anscolor[0]=196;
        anscolor[1]=183;
        anscolor[2]=215;
        break;
    default:
        break;
    }
    return anscolor;
}


void ETheme::updateColorGlobally(MainWindow *mainwind)
{
    getFileMenuStyle();
    mainwind->menubar->setStyleSheet(getMenubarStyle());
    mainwind->explorer->setStyleSheet(getExplorerStyle());
    mainwind->editor->setStyleSheet(getEditorStyle());
    setEditorFontColor(mainwind);
    mainwind->editor->efilebar->setStyleSheet(getExplorerStyle());
    mainwind->editor->edit->lineColor.setRgb(getLineColorStyle(),getLineColorStyle(),getLineColorStyle());
    mainwind->editor->edit->currentLineColor.setRgb(getCurrentLineColorStyle(),getCurrentLineColorStyle(),getCurrentLineColorStyle());
    mainwind->menubar->fileMenu->setPalette(QColor(anscolor[0],anscolor[1],anscolor[2]));
    mainwind->menubar->editMenu->setPalette(QColor(anscolor[0],anscolor[1],anscolor[2]));
    mainwind->menubar->runMenu->setPalette(QColor(anscolor[0],anscolor[1],anscolor[2]));
    mainwind->menubar->appearanceMenu->setPalette(QColor(anscolor[0],anscolor[1],anscolor[2]));
    mainwind->menubar->themeMenu->setPalette(QColor(anscolor[0],anscolor[1],anscolor[2]));
    mainwind->menubar->helpMenu->setPalette(QColor(anscolor[0],anscolor[1],anscolor[2]));

}
