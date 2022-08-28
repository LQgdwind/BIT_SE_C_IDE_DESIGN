#ifndef EFILEBAR_H
#define EFILEBAR_H

#include <QWidget>
#include "helper.h"
#include "efilelabel.h"

class EfileBar : public QWidget
{
    Q_OBJECT
public:
    explicit EfileBar(QWidget *parent = nullptr);
    QTextEdit *edit;
    QHBoxLayout *layout;
    void open_file(QString file);
signals:

public slots:
};

#endif // EFILEBAR_H