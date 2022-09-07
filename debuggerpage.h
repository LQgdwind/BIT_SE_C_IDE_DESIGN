#ifndef DEBUGGERPAGE_H
#define DEBUGGERPAGE_H

#include <QWidget>
#include <debugger.h>

namespace Ui {
class debuggerPage;
}

class debuggerPage : public QWidget
{
    Q_OBJECT

public:
    explicit debuggerPage(QWidget *parent = 0);
    void initializeDebugger(QString debugPath);
    ~debuggerPage();

private slots:
    void on_runBtn_clicked();

    void on_continueBtn_clicked();

    void on_setBtn_clicked();

    void on_deleteBtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void reLoadTable();
private:
    Ui::debuggerPage *ui;
    Debugger *debugger;
};

#endif // DEBUGGERPAGE_H