#ifndef ECODEEDIT_H
#define ECODEEDIT_H

#include <QPlainTextEdit>
#include <QObject>
#include <QPainter>
#include <QListWidget>
#include <QListWidgetItem>
#include "highlighter.h"
#include <algorithm>
#include "completelistwidget.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

class EcodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    EcodeEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void setUpCompleteList();
    bool saveToFile(const QString &name);
    QColor lineColor;
    QColor currentLineColor;
    void allhideline(bool foldorunfold);
    void allhidenoteline(bool foldorunfold);
//    void hideline();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void showCompleteWidget();
    void hideline();
    void hidenoteline();
    //void completeWidgetKeyDown();

private:
    QWidget *lineNumberArea;
    QColor editorColor;
    QStringList completeList;//储存自动填充的关键字
    CompleteListWidget *completeWidget;
    QString getWordOfCursor();
    int completeState;
    int getCompleteWidgetX();
    Highlighter *highlighter;
    void setUpHighlighter();

//    int linenum;
//    void hideline();

};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(EcodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    EcodeEditor *codeEditor;
};
enum CompleteState{
    Ignore=0,
    Showing=1,
    Hide=2
};

#endif // ECODEEDIT_H
