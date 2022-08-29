#ifndef EMENU_H
#define EMENU_H

#include <QWidget>
#include "helper.h"
#include "editor.h"
#include "explorer.h"
#include "finddialog.h"
#include "replacedialog.h"

class EMenu : public QMenuBar
{
    Q_OBJECT
private:
public:
    explicit EMenu(QWidget *parent = nullptr);
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *runMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QAction *openFolderAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *newFileAct;

    QAction *undoAct;
    QAction *redoAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *cutAct;

    QAction *compileAct;
    QAction *findAct;
    QAction *replaceAct;
    QAction *beautifyAct;
    QAction *runAct;
    Editor *editor;
    Explorer *explorer;

    QClipboard * clipboard;
private:
    bool isQualified();
    FindDialog *finddialog;
    ReplaceDialog *replacedialog;
signals:
    void run_signal();
    void compile_signal();
public slots:
    void on_open_click();
    void on_open_folder_click();
    void on_save_click();
    void on_new_file_click();
    void on_save_as_click();

    void on_copy_click();
    void on_paste_click();
    void on_cut_click();
    void on_undo_click();
    void on_redo_click();
    void on_find_click();
    void on_replace_click();
    void on_beautify_click();

    void on_compile_click();
    void on_run_click();
};

#endif // EMENU_H
