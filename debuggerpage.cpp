#include "debuggerpage.h"
#include "ui_debuggerpage.h"

debuggerPage::debuggerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::debuggerPage)
{
    ui->setupUi(this);
}

debuggerPage::~debuggerPage()
{
    delete ui;
}

void debuggerPage::on_runBtn_clicked()
{
    this->debugger->cmd_run();
    reLoadTable();
}

void debuggerPage::on_continueBtn_clicked()
{
    this->debugger->cmd_continue();
    reLoadTable();
}

void debuggerPage::on_setBtn_clicked()
{
    this->debugger->cmd_setBreakPoint(ui->setEdit->text().toInt());
    return;
}

void debuggerPage::on_deleteBtn_clicked()
{
    this->debugger->cmd_deleteBreakPoint(ui->deleteEdit->text().toInt());
    return;
}

void debuggerPage::on_pushButton_clicked()
{
    this->debugger->startProgram();;
}

void debuggerPage::on_pushButton_2_clicked()
{
    this->debugger->endProgram();
}

void debuggerPage::reLoadTable(){
    for(int i = 0; i < ui->tableWidget->rowCount(); i++){
        if(ui->tableWidget->item(i, 0) == NULL)
            continue;
        QString valName = ui->tableWidget->item(i, 0)->text();
        qDebug()<<"Valname is" << valName;
        if(valName.size() != 0){
            int value = debugger->printVal(ui->tableWidget->item(i, 0)->text());
            if(value != -35575)
                ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(value)));
            else
                ui->tableWidget->setItem(i, 1, new QTableWidgetItem("(No value)"));
        }
        else
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(""));
    }
}

void debuggerPage::initializeDebugger(QString debugPath){
    this->debugger = new Debugger(debugPath);
    this->debugger->startProgram();
}
