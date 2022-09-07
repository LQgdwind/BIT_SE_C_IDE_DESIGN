#ifndef BUILD_H
#define BUILD_H
#include "emenu.h"
#include <Qdir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <windows.h>

#define DEFAULT_BUILD_PATH "C:/Users/Administrator/Desktop/testc"//默认位置指定

class Build : public QWidget
{
    Q_OBJECT
public:
    explicit Build(EMenu*,QWidget *parent = nullptr);
    EMenu* emenu;
signals:
private:
    QDir buildDir;
public slots:
    void eRun();
    void eCompile();
    void eMultiCompile();
    void setBuildDir(QDir buildDir);
};

#endif // BUILD_H