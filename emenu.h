#ifndef EMENU_H
#define EMENU_H

#include <QWidget>
#include "helper.h"
#include "editor.h"
#include "explorer.h"

class EMenu : public QMenuBar
{
    Q_OBJECT
private:
    bool is_open ;
    bool is_new_file ;
    QString file_name_current;
    QString file_string_current;
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

    QAction *beautifyAct;
    QAction *findAct;

    QAction *runAct;
    Editor *editor;
    Explorer *explorer;

    QClipboard * clipboard;

    bool openTextByStream(const QString &aFileName);
    bool saveTextByStream(const QString &aFileName);
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

    void on_compile_click();
    void on_run_click();
};

#endif // EMENU_H
