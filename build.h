#ifndef BUILD_H
#define BUILD_H
#include "emenu.h"
#include <Qdir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <windows.h>

class Build : public QWidget
{
    Q_OBJECT
public:
    explicit Build(EMenu*,QWidget *parent = nullptr);
    void setBuildDir(QDir buildDir);
    EMenu* emenu;
signals:
private:
    QDir buildDir;
public slots:
    void eRun();
    void eCompile();
};

#endif // BUILD_H

