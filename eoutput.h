#ifndef EOUTPUT_H
#define EOUTPUT_H

#include <QWidget>
#include "helper.h"

class EOutPut : public QWidget
{
    Q_OBJECT
public:
    explicit EOutPut(QWidget *parent = nullptr);
    QTextBrowser *textBrowser;
    QVBoxLayout *layout;
private:
    void printForUiDesign();
    void initialEoutput();
signals:

public slots:
};

#endif // EOUTPUT_H
