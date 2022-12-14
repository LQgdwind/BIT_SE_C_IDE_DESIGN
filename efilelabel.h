#ifndef EFILELABEL_H
#define EFILELABEL_H

#include <QWidget>
#include "helper.h"
#include <QPlainTextEdit>

#include "ecodeedit.h"

class EFileLabel : public QWidget
{
    Q_OBJECT
public:
    explicit EFileLabel(QString filePath,QWidget *parent = nullptr);
    QHBoxLayout *layout;
    QPushButton *openFile,*exitFile;
    void updateLabelName();
    void updateCommitStatus(bool status);
    bool getChangeUnCommit() const;
    bool getIsChosen() const;
    void setIsChosen(bool value);
    QString getFilePath() const;
    void setFilePath(const QString &value);
signals:
    void openClicked(QString s);
    void closeClicked(QString s);
private:
    setupLayout();
    QString filePath;
    QString fileName;
    bool isChosen{true};
    bool changeUnCommit{false};
public slots:
    void handleUncommitChange();
    void on_open_file_click();
    void on_close_file_click();
};

#endif // EFILELABEL_H
