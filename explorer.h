#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include "editor.h"
#include "helper.h"
#include "efilebar.h"
#include "ecodeedit.h"

class EMenu;
class Explorer : public QWidget
{
    Q_OBJECT
public:
    explicit Explorer(QWidget *parent = nullptr);
    QTreeWidget *fileTree;
    QListWidget *functionTree;
    QVBoxLayout *layout;
    QLabel *header;
    Editor *editor;
    EcodeEditor *edit;
    EMenu *menu;
    void addRootDir(QDir dir);
    QTreeWidgetItem *findSelectedDir();
private:
    void addNode(QFileInfo &info,QTreeWidgetItem *root);
    void setupLayout();
    void deleteItem(QTreeWidgetItem *item);
    QList<QTextCursor> curs;
signals:
    void fileRenamed(QString oldName,QString newName);
    void fileDeleted(QString fileName);
public slots:
    void open_in_editor(QTreeWidgetItem *item,int column);
    void handleMenuRequested(QPoint pos);
    void refreshFunctionReference(EcodeEditor *curEditor);
    void handleFunctionRefClicked(QListWidgetItem *item);
};

#endif // EXPLORER_H
