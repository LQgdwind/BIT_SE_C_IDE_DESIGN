#ifndef ESIDEBAR_H
#define ESIDEBAR_H

#include <QWidget>
#include <QPushButton>
#include "emenu.h"

class ESideBar : public QWidget
{
    Q_OBJECT
public:
    explicit ESideBar(QWidget *parent = nullptr);
    QPushButton* exploreBtn;
    QPushButton* searchBtn;
    QPushButton* runBtn;
    QPushButton* debugBtn;
    QPushButton* compileBtn;
    void appendActions(EMenu *menu);
signals:

public slots:
};

#endif // ESIDEBAR_H
