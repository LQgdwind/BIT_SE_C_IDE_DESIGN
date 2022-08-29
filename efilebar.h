#ifndef EFILEBAR_H
#define EFILEBAR_H

#include <QWidget>
#include "helper.h"
#include "efilelabel.h"
#include "ecodeedit.h"
#include "efileinfo.h"

class EfileBar : public QWidget
{
    Q_OBJECT
public:
    explicit EfileBar(QWidget *parent = nullptr);
    //Ecode *edit;
    QHBoxLayout *layout;
    QString curEditing;
    QMap<QString,EFileInfo>openedFiles;
    void open_file(QString file);
signals:
    void updateEdit(EcodeEditor *curEdit);
public slots:
    void showLabel(QString name);
    void deleteLabel(QString name);
};

#endif // EFILEBAR_H
