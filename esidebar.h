#ifndef ESIDEBAR_H
#define ESIDEBAR_H

#include <QWidget>
#include <QPushButton>

class ESideBar : public QWidget
{
    Q_OBJECT
public:
    explicit ESideBar(QWidget *parent = nullptr);
    QPushButton* exploreBtn;
    QPushButton* searchBtn;
    QPushButton* runBtn;
    QPushButton* compileBtn;

signals:

public slots:
};

#endif // ESIDEBAR_H