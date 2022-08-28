#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include "eoutput.h"
#include "helper.h"
#include "efilebar.h"

class Editor : public QWidget
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = nullptr);
    QVBoxLayout *layout;
    EfileBar *efilebar;
    QTextEdit *edit;
    QLabel *eoutputlabel;
    EOutPut *eoutput;
private:
    void setupLayout();
signals:

public slots:
};

#endif // EDITOR_H
