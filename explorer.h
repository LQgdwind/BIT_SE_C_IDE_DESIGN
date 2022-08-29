#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include "editor.h"
#include "helper.h"
#include "efilebar.h"

class Explorer : public QWidget
{
    Q_OBJECT
public:
    explicit Explorer(QWidget *parent = nullptr);
    QTreeWidget *fileTree;
    QVBoxLayout *layout;
    QLabel *header;
    Editor *editor;
    void addRootDir(QDir dir);
    QTreeWidgetItem *findSelectedDir();
private:
    void addNode(QFileInfo &info,QTreeWidgetItem *root);
    void setupLayout();
signals:

public slots:
    void open_in_editor(QTreeWidgetItem *item,int column);
};

#endif // EXPLORER_H
