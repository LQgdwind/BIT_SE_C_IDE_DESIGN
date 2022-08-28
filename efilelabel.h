#ifndef EFILELABEL_H
#define EFILELABEL_H

#include <QWidget>
#include "helper.h"

class EFileLabel : public QWidget
{
    Q_OBJECT
public:
    explicit EFileLabel(QString filePath,QTextEdit *edit,QWidget *parent = nullptr);
    QHBoxLayout *layout;
    QPushButton *openFile,*exitFile;
    QTextEdit *edit;
    QString filePath;
signals:

private:
    setupLayout();
public slots:
    void on_open_file_click();
    void on_close_file_click();
};

#endif // EFILELABEL_H
