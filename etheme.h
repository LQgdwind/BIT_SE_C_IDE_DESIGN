#ifndef ETHEME_H
#define ETHEME_H
#include <QString>
class MainWindow;
class ETheme
{
public:
    enum THEME{
        black,
        white,
        blue
    };
    static THEME curTheme;
    static void updateColorGlobally(MainWindow *mainwind);
private:
    static QString getMenubarStyle();
//    static QString getSidebarStyle();
    static QString getExplorerStyle();
    static QString getEditorStyle();
    static void setEditorFontColor(MainWindow *mainwidow);
    static int getLineColorStyle();
    static int getCurrentLineColorStyle();
    static int * getFileMenuStyle();
//    static QString getOpenFileStyle();
};

#endif // ETHEME_H
