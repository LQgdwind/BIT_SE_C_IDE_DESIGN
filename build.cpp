#include "build.h"
//using for test
//#define DIR_PATH "C:/Users/83515/Desktop/Worktable/Beijing Institude of Technology/College of Computer Science/5th Semester/IDE/test"

#define SOURCE_FILENAME "src.c"
#define EXE_FILENAME "debug.exe"

Build::Build(EMenu* parentmenu, QWidget *parent) : QWidget(parent)
{
    this->emenu = parentmenu;
    this->buildDir = QDir::currentPath();
    connect(this->emenu,SIGNAL(run_signal()),this,SLOT(eRun()));
    connect(this->emenu,SIGNAL(compile_signal()),this,SLOT(eCompile()));
}

void Build::eRun()
{
    this->emenu->editor->eoutput->textBrowser->append("Run");

    QString programPath = QDir::currentPath();
    QString buildPath = buildDir.path();

//  Create .bat for running.
    QFileInfo batInfo(buildPath+"/debug", "run.bat");
    QFile file(batInfo.absoluteFilePath());
    file.open(QIODevice::WriteOnly);

//  Using QT/Tools/bin/gcc
    QTextStream out(&file);
    out<<EXE_FILENAME<<endl;
    out<<"pause";
    file.close();

    QDir::setCurrent(buildPath+"/debug");
    QProcess process;
    process.setProgram("run.bat");
    process.setWorkingDirectory(buildPath+"/debug");
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    process.setProcessEnvironment(env);
    process.setCreateProcessArgumentsModifier([this](QProcess::CreateProcessArguments *args){
        args->flags |= CREATE_NEW_CONSOLE;
        args->startupInfo->dwFlags &= ~STARTF_USESTDHANDLES;
    });

    process.start();

    if(process.waitForStarted()){
        qDebug()<<"program started.";
    }
    else{
        qDebug()<<"program start failed."<<process.errorString();
    }

    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAll());

    QDir::setCurrent(programPath);
    //QString contains = this->editor->edit->toPlainText();
    //单文件包含的内容
}

void Build::eCompile()
{
    this->emenu->editor->eoutput->textBrowser->append("Compile");
    QString programPath = QDir::currentPath();
    QString buildPath = buildDir.path();

    QDir::setCurrent(buildDir.path());
    if(!buildDir.exists("debug")){
        buildDir.mkdir("debug");
    }
    QDir::setCurrent(buildPath + "/debug");

//  Save source code
    QFileInfo srcInfo(buildPath + "/debug", SOURCE_FILENAME);
    QFile src(srcInfo.absoluteFilePath());
    src.open(QIODevice::WriteOnly);

    QTextStream srcTextStream(&src);
    srcTextStream << this->emenu->editor->edit->toPlainText();
    src.close();

//  Create .bat for compiling.
    QFileInfo batInfo(buildPath+"/debug", "build.bat");
    QFile file(batInfo.absoluteFilePath());
    file.open(QIODevice::WriteOnly);

//  Using QT/Tools/bin/gcc
    QTextStream out(&file);
    out << QString("set PATH=%1\\Tools\\bin;%PATH%").arg(QDir::toNativeSeparators(buildPath)) << endl;
    out << QString(QString("cd /D %1").arg(QDir::toNativeSeparators(QDir::currentPath()))) << endl;
    out << QString("gcc %1 -o %2").arg(SOURCE_FILENAME).arg(EXE_FILENAME) << endl;
    file.close();

    QProcess process;
    QDir::setCurrent(buildPath + "/debug/build.bat");
    process.start("build.bat");

    if(process.waitForStarted()){
        qDebug()<<"program started.";
    }
    else{
        qDebug()<<"program start failed."<<process.errorString();
    }
    process.waitForFinished();

    this->emenu->editor->eoutput->textBrowser->append(QString::fromLocal8Bit(process.readAllStandardError()));
    this->emenu->editor->eoutput->textBrowser->append(QString::fromLocal8Bit(process.readAllStandardOutput()));

    qDebug()<<QString::fromLocal8Bit(process.readAllStandardError());
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput());

    QDir::setCurrent(programPath);  // Reset path.
}
