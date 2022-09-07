#ifndef EMENU_H
#define EMENU_H

#include <QWidget>
#include "helper.h"
#include "editor.h"
#include "explorer.h"
#include "finddialog.h"
#include "replacedialog.h"

class MainWindow;
class EMenu : public QMenuBar
{
    Q_OBJECT
public:
    QString buildPath;
private:
public:
    explicit EMenu(QWidget *parent = nullptr);
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *runMenu;
    QMenu *helpMenu;
    QMenu *themeMenu;
    QMenu *appearanceMenu;

    QAction *learnAct;

    QAction *fontAct;
    QAction *colorAct;
    QAction *darkAct;
    QAction *whiteAct;
    QAction *blueAct;

    QAction *openAct;
    QAction *openFolderAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *newFileAct;
    QAction *newFolderAct;

    QAction *undoAct;
    QAction *redoAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *cutAct;
    QAction *allfoldAct;
    QAction *allunfoldAct;

    QAction *compileAct;
    QAction *findAct;
    QAction *replaceAct;
    QAction *debugAct;
    QAction *runAct;
    Editor *editor;
    Explorer *explorer;
    QClipboard * clipboard;
    MainWindow *mainwind;
private:
    bool isQualified();
    FindDialog *finddialog;
    ReplaceDialog *replacedialog;
signals:
    void run_signal();
    void compile_signal();
    void selected_folder(QDir);
public slots:
    void on_learn_click();
    void on_open_click();
    void on_open_folder_click();
    void on_save_click();
    void on_new_file_click();
    void on_save_as_click();
    void on_new_folder_click();
    void on_copy_click();
    void on_paste_click();
    void on_cut_click();
    void on_undo_click();
    void on_redo_click();
    void on_find_click();
    void on_replace_click();
    void on_font_click();
    void on_compile_click();
    void on_run_click();
    void on_color_click();
    void on_dark_click();
    void on_white_click();
    void on_blue_click();
    void on_allfold_click();
    void on_allunfold_click();
    void on_debug_click();
};

#endif // EMENU_H
