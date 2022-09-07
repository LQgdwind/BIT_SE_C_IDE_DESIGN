#include <QtWidgets>
#include <QDebug>
#include "ecodeedit.h"

int linenum;
int isornot[2000] = {0};

EcodeEditor::EcodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{

    lineNumberArea = new LineNumberArea(this);
    updateLineNumberAreaWidth(0);
    currentLineColor = QColor(30,30,30);//只读时高亮条颜色
//  highlightCurrentLine();

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(cursorPositionChanged()),this,SLOT(showCompleteWidget()));
    connect(this, SIGNAL(selectionChanged()),this,SLOT(hideline()));
    connect(this, SIGNAL(selectionChanged()),this,SLOT(hidenoteline()));


    //set color value
    lineColor.setRgb(30,30,30); //数字条背景色
//    //editorColor.setRgb(255,255,255); //codeEdit背景色

//    //set background color
//    QPalette p = this->palette();
//    p.setColor(QPalette::Active, QPalette::Base, editorColor);
//    p.setColor(QPalette::Inactive, QPalette::Base, editorColor);
//    p.setColor(QPalette::Text,Qt::black);
//    this->setPalette(p);

    //初始化补全列表
    setUpCompleteList();
    completeWidget= new CompleteListWidget(this);
    completeWidget->hide();
    completeWidget->setMaximumHeight(fontMetrics().height()*5);
    completeState=CompleteState::Hide;

    //高亮
    setUpHighlighter();
}

int EcodeEditor::lineNumberAreaWidth() //行号区域宽度
{
    int digits = 1;//行数数字的位数
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    if(digits < 3) digits=3;

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

//设定左边留白的宽度，参数无效，没有用到
void EcodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

//文本框滚动时同时滚动行数
void EcodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);

}

//尺寸调整函数
void EcodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


void EcodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!this->isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(currentLineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

//打印行号，此函数被paintEvent 调用，paintEvent在头文件里被重写
void EcodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    if (!isReadOnly())
    {
        currentLineColor = QColor(100,100,100).lighter(160);//编辑时高亮条颜色
        QPainter painter(lineNumberArea);
        painter.fillRect(event->rect(), lineColor);

        QTextBlock block = firstVisibleBlock();
        int blockNumber = block.blockNumber();
        int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
        int bottom = top + (int) blockBoundingRect(block).height();

        while (block.isValid() && top <= event->rect().bottom())
        {
            if (block.isVisible() && bottom >= event->rect().top())
            {
                QString number = QString::number(blockNumber + 1);
                painter.setPen(Qt::lightGray);
                painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                                 Qt::AlignCenter, number);

            }
            block = block.next();
            top = bottom;
            bottom = top + (int) blockBoundingRect(block).height();
            ++blockNumber;
            if(linenum < blockNumber) linenum = blockNumber;
        }

    }
}

void EcodeEditor::hideline()
{
    int linenumber[linenum];
    int hide = 0;
    int hidelinenumber[linenum];
    int hide1 = 0;
    int hidelinenumber1[linenum];
    int hide2 = 0;
    int hidelinenumber2[linenum];

    for(int i = 0; i < linenum;i++)
    {
        linenumber[i] = i + 1;
        QTextBlock blocktemp = this->document()->findBlockByNumber(i);
        if(blocktemp.text().contains("{")) linenumber[i]++;
        if(blocktemp.text().contains("}")) linenumber[i]--;
    }
    for(int i = 0; i < linenum;i++)
    {

        if(linenumber[i] == i+2)
        {
            hidelinenumber1[hide1]=linenumber[i] - 1;
            hide1++;
        }
        if(linenumber[i] == i)
        {
            hidelinenumber2[hide2]=linenumber[i] + 1;
            hide2++;
            if(hide1 == hide2)
            {
                hidelinenumber[hide] = hide2-1;
                hide++;
            }
        }
    }

    int row = this->textCursor().blockNumber();
    qDebug()<<this->document()->findBlockByLineNumber(row+1).text();
    if(this->document()->findBlockByLineNumber(row+1).text().contains("{"))
    {
        int hidetemp=0,hidetemp1=0,hidetemp2=0;
        int left = 1;
        for(int i = 0; i < hide1;i++)
        {
            if(hidelinenumber1[i] == row+2) hidetemp1 = i;
        }
        for(int i = 0; i < hide1;i++)
        {
            if(hidelinenumber1[hidelinenumber[i]] >= row+2)
            {
                hidetemp = hidelinenumber[i];
                break;
            }

        }
        for(int i = row+3;i <= hidelinenumber2[hidetemp];i++)
        {
            if(this->document()->findBlockByLineNumber(i-1).text().contains("{")) left++;
            if(this->document()->findBlockByLineNumber(i-1).text().contains("}")) left--;
            if((this->document()->findBlockByLineNumber(i-1).text().contains("}")) && (left==0))
            {
                hidetemp2=i;
                break;
            }

        }
        if(isornot[hidelinenumber1[hidetemp1]-1] == 0)
        {
            for(int i = row+2;i <= hidetemp2;i++)
            {
                QTextBlock myTextBlock = this->document()->findBlockByNumber(i-1);

                myTextBlock.setVisible(false);
            }
            this->repaint();
            isornot[hidelinenumber1[hidetemp1]-1] = 1;
        }
        else
        {
            for(int i = row+2;i <= hidetemp2;i++)
            {
                QTextBlock myTextBlock = this->document()->findBlockByNumber(i-1);

                myTextBlock.setVisible(true);
            }
            this->repaint();
            isornot[hidelinenumber1[hidetemp1]-1] = 0;
        }
    }
}

void EcodeEditor::hidenoteline()
{
    int linenumber[linenum];
    int hide = 0;
    int hidelinenumber[linenum];
    int hide1 = 0;
    int hidelinenumber1[linenum];
    int hide2 = 0;
    int hidelinenumber2[linenum];

    for(int i = 0; i < linenum;i++)
    {
        linenumber[i] = i + 1;
        QTextBlock blocktemp = this->document()->findBlockByNumber(i);
        if(blocktemp.text().contains("/*")) linenumber[i]++;
        if(blocktemp.text().contains("*/")) linenumber[i]--;
    }
    for(int i = 0; i < linenum;i++)
    {

        if(linenumber[i] == i+2)
        {
            hidelinenumber1[hide1]=linenumber[i] - 1;
            hide1++;
        }
        if(linenumber[i] == i)
        {
            hidelinenumber2[hide2]=linenumber[i] + 1;
            hide2++;
            if(hide1 == hide2)
            {
                hidelinenumber[hide] = hide2-1;
                hide++;
            }
        }
    }

    int row = this->textCursor().blockNumber();
    if(this->document()->findBlockByLineNumber(row).text().contains("/*"))
    {
        int hidetemp=0,hidetemp1=0,hidetemp2=0;
        int left = 1;
        for(int i = 0; i < hide1;i++)
        {
            if(hidelinenumber1[i] == row+1) hidetemp1 = i;
        }
        for(int i = 0; i < hide1;i++)
        {
            if(hidelinenumber1[hidelinenumber[i]] >= row+1)
            {
                hidetemp = hidelinenumber[i];
                break;
            }

        }
        for(int i = row+2;i <= hidelinenumber2[hidetemp];i++)
        {
            if(this->document()->findBlockByLineNumber(i-1).text().contains("/*")) left++;
            if(this->document()->findBlockByLineNumber(i-1).text().contains("*/")) left--;
            if((this->document()->findBlockByLineNumber(i-1).text().contains("*/")) && (left==0))
            {
                hidetemp2=i;
                break;
            }

        }
        if(isornot[hidelinenumber1[hidetemp1]-1] == 0)
        {
            for(int i = row+2;i <= hidetemp2;i++)
            {
                QTextBlock myTextBlock = this->document()->findBlockByNumber(i-1);

                myTextBlock.setVisible(false);
            }
            this->repaint();
            isornot[hidelinenumber1[hidetemp1]-1] = 1;
        }
        else
        {
            for(int i = row+2;i <= hidetemp2;i++)
            {
                QTextBlock myTextBlock = this->document()->findBlockByNumber(i-1);

                myTextBlock.setVisible(true);
            }
            this->repaint();
            isornot[hidelinenumber1[hidetemp1]-1] = 0;
        }
    }
}

void EcodeEditor::allhideline(bool foldorunfold)
{
    int linenumber[linenum];
    int hide = 0;
    int hidelinenumber[linenum];
    int hide1 = 0;
    int hidelinenumber1[linenum];
    int hide2 = 0;
    int hidelinenumber2[linenum];

    for(int i = 0; i < linenum;i++)
    {
        linenumber[i] = i + 1;
        QTextBlock blocktemp = this->document()->findBlockByNumber(i);
        if(blocktemp.text().contains("{")) linenumber[i]++;
        if(blocktemp.text().contains("}")) linenumber[i]--;
    }
    for(int i = 0; i < linenum;i++)
    {

        if(linenumber[i] == i+2)
        {
            hidelinenumber1[hide1]=linenumber[i] - 1;
            hide1++;
        }
        if(linenumber[i] == i)
        {
            hidelinenumber2[hide2]=linenumber[i] + 1;
            hide2++;
            if(hide1 == hide2)
            {
                hidelinenumber[hide] = hide2-1;
                hide++;
            }
        }
    }

    for(int row = 0;row <= linenum;row++)
    {
        if(this->document()->findBlockByLineNumber(row+1).text().contains("{"))
        {
            int hidetemp=0,hidetemp1=0,hidetemp2=0;
            int left = 1;
            for(int i = 0; i < hide1;i++)
            {
                if(hidelinenumber1[i] == row+2) hidetemp1 = i;
            }
            for(int i = 0; i < hide1;i++)
            {
                if(hidelinenumber1[hidelinenumber[i]] >= row+2)
                {
                    hidetemp = hidelinenumber[i];
                    break;
                }

            }
            for(int i = row+3;i <= hidelinenumber2[hidetemp];i++)
            {
                if(this->document()->findBlockByLineNumber(i-1).text().contains("{")) left++;
                if(this->document()->findBlockByLineNumber(i-1).text().contains("}")) left--;
                if((this->document()->findBlockByLineNumber(i-1).text().contains("}")) && (left==0))
                {
                    hidetemp2=i;
                    break;
                }

            }
            if(foldorunfold)
            {
                for(int i = row+2;i <= hidetemp2;i++)
                {
                    QTextBlock myTextBlock = this->document()->findBlockByNumber(i-1);

                    myTextBlock.setVisible(false);
                }
                this->repaint();
                isornot[2000] = {1};
            }
            else
            {
                for(int i = row+2;i <= hidetemp2;i++)
                {
                    QTextBlock myTextBlock = this->document()->findBlockByNumber(i-1);

                    myTextBlock.setVisible(true);
                }
                this->repaint();
                isornot[2000] = {0};
            }
        }
    }
}

void EcodeEditor::allhidenoteline(bool foldorunfold)
{
    int linenumber[linenum];
    int hide = 0;
    int hidelinenumber[linenum];
    int hide1 = 0;
    int hidelinenumber1[linenum];
    int hide2 = 0;
    int hidelinenumber2[linenum];

    for(int i = 0; i < linenum;i++)
    {
        linenumber[i] = i + 1;
        QTextBlock blocktemp = this->document()->findBlockByNumber(i);
        if(blocktemp.text().contains("/*")) linenumber[i]++;
        if(blocktemp.text().contains("*/")) linenumber[i]--;
    }
    for(int i = 0; i < linenum;i++)
    {

        if(linenumber[i] == i+2)
        {
            hidelinenumber1[hide1]=linenumber[i] - 1;
            hide1++;
        }
        if(linenumber[i] == i)
        {
            hidelinenumber2[hide2]=linenumber[i] + 1;
            hide2++;
            if(hide1 == hide2)
            {
                hidelinenumber[hide] = hide2-1;
                hide++;
            }
        }
    }

    for(int row = 0;row <= linenum;row++)
    {
        if(this->document()->findBlockByLineNumber(row).text().contains("/*"))
        {
            int hidetemp=0,hidetemp1=0,hidetemp2=0;
            int left = 1;
            for(int i = 0; i < hide1;i++)
            {
                if(hidelinenumber1[i] == row+1) hidetemp1 = i;
            }
            for(int i = 0; i < hide1;i++)
            {
                if(hidelinenumber1[hidelinenumber[i]] >= row+1)
                {
                    hidetemp = hidelinenumber[i];
                    break;
                }

            }
            for(int i = row+2;i <= hidelinenumber2[hidetemp];i++)
            {
                if(this->document()->findBlockByLineNumber(i-1).text().contains("/*")) left++;
                if(this->document()->findBlockByLineNumber(i-1).text().contains("*/")) left--;
                if((this->document()->findBlockByLineNumber(i-1).text().contains("*/")) && (left==0))
                {
                    hidetemp2=i;
                    break;
                }

            }
            if(foldorunfold)
            {
                for(int i = row+2;i <= hidetemp2;i++)
                {
                    QTextBlock myTextBlock = this->document()->findBlockByNumber(i-1);

                    myTextBlock.setVisible(false);
                }
                this->repaint();
                isornot[2000] = 1;
            }
            else
            {
                for(int i = row+2;i <= hidetemp2;i++)
                {
                    QTextBlock myTextBlock = this->document()->findBlockByNumber(i-1);

                    myTextBlock.setVisible(true);
                }
                this->repaint();
                isornot[2000] = 0;
            }
        }
    }

}

//自动补全
void EcodeEditor::keyPressEvent(QKeyEvent *event){
  //qDebug()<<event->key();
    if(event->modifiers()==Qt::ShiftModifier&&event->key()==40){
        this->insertPlainText(tr("()"));
        this->moveCursor(QTextCursor::PreviousCharacter);
    }
    else if(event->modifiers()==Qt::ShiftModifier&&event->key()==34){
        this->insertPlainText(tr("\"\""));
        this->moveCursor(QTextCursor::PreviousCharacter);
    }
    else if(event->key()==16777235&&completeState==CompleteState::Showing){
        if(completeWidget->currentRow()>0)
        completeWidget->setCurrentRow(completeWidget->currentRow()-1);
    }
    else if(event->key()==16777237&&(completeState==CompleteState::Showing)){
      if(completeWidget->currentRow()<completeWidget->count()-1)
        completeWidget->setCurrentRow(completeWidget->currentRow()+1);
    }
    else if(event->key()==Qt::Key_Return&&(completeState==CompleteState::Showing)){
        QString insertText=completeWidget->currentItem()->text();
        QString word=this->getWordOfCursor();
        completeState=CompleteState::Ignore;
        for(int i=0;i<word.count();++i)
            this->textCursor().deletePreviousChar();

         this->insertPlainText(insertText);
        if(insertText.contains(tr("#include")))
            this->moveCursor(QTextCursor::PreviousCharacter);
        completeState=CompleteState::Hide;
        completeWidget->hide();
    }//*
    else if(event->key()==Qt::Key_Return){//回车下行层级自动缩进功能
      //获得本行的文本
        QString temp=this->document()->findBlockByLineNumber(this->textCursor().blockNumber()).text();
        QPlainTextEdit::keyPressEvent(event);
        if(temp.count()<=0)return;
      //输出回车那一行的前距
        foreach(const QChar &c,temp){
            if(c.isSpace())this->insertPlainText(c);
            else break;
        }
      //如果是for() while() switch() if()则缩进一个tab,一种粗略地做法可能会出错
      if(temp.at(temp.count()-1)==')'&&(temp.contains(tr("for("))||temp.contains(tr("while("))
                                        ||temp.contains(tr("switch("))||temp.contains(tr("if("))))
          this->insertPlainText(tr("\t"));
      //如果是{ 则缩进并补}
      if(temp.at(temp.count()-1)=='{'){
          this->insertPlainText(tr("\t"));
          QTextCursor cursor=this->textCursor();
          int pos=this->textCursor().position();
          this->insertPlainText(tr("\n"));
          foreach(const QChar &c,temp){
              if(c.isSpace())this->insertPlainText(c);
              else break;
          }
          this->insertPlainText(tr("}"));
          cursor.setPosition(pos);
          this->setTextCursor(cursor);//返回中间一行
        }
    }//*/
    else if(event->key()==Qt::Key_Backspace){
        switch(this->document()->characterAt(this->textCursor().position()-1).toLatin1()){
        case '(':
            QPlainTextEdit::keyPressEvent(event);
            if(this->document()->characterAt(this->textCursor().position())==')'){
                this->textCursor().deleteChar();
            }break;
        case '\"':
            QPlainTextEdit::keyPressEvent(event);
            if(this->document()->characterAt(this->textCursor().position())=='\"'){
                this->textCursor().deleteChar();
            }break;
        case '<':
             QPlainTextEdit::keyPressEvent(event);
            if(this->document()->characterAt(this->textCursor().position())=='>'){
                this->textCursor().deleteChar();
            }break;
        default:
          QPlainTextEdit::keyPressEvent(event);
        }
    }
  else{
        QPlainTextEdit::keyPressEvent(event);
        //qDebug()<<event->key();
    }
}

void EcodeEditor::setUpCompleteList(){
  completeList<< "char" << "class" << "const"
              << "double" << "enum" << "explicit"
              << "friend" << "inline" << "int"
              << "long" << "namespace" << "operator"
              << "private" << "protected" << "public"
              << "short" << "signals" << "signed"
              << "slots" << "static" << "struct"
              << "template" << "typedef" << "typename"
              << "union" << "unsigned" << "virtual"
              << "void" << "volatile" << "bool"<<"using"<<"constexpr"
              <<"sizeof"<<"if"<<"for"<<"foreach"<<"while"<<"do"<<"case"
              <<"break"<<"continue"<<"template"<<"delete"<<"new"
              <<"default"<<"try"<<"return"<<"throw"<<"catch"<<"goto"<<"else"
             <<"extren"<<"this"<<"switch"<<"#include \"\""<<"#include <>"<<"#define"<<"stdio.h"<<"stdlib.h";
}

bool EcodeEditor::saveToFile(const QString &name)
{
    QFile aFile(name);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile);
    QString str=toPlainText();
    aStream<<str;
    aFile.close();
}

//得到当前光标位置的字符串
QString EcodeEditor::getWordOfCursor(){
    int pos=this->textCursor().position()-1;
    QVector<QChar> words;
    QString result;
    QChar ch=this->document()->characterAt(pos+1);
    if(ch.isDigit()||ch.isLetter()||ch==' ')return result;
    ch=this->document()->characterAt(pos);
     if(ch==' ')return result;
    while(ch.isDigit()||ch.isLetter()||ch=='_'||ch=='#'){
        words.append(ch);
        pos--;
        ch=this->document()->characterAt(pos);
    }
    for(int i=words.size()-1;i>=0;i--)
        result+=words[i];
    return result;

}

void EcodeEditor::showCompleteWidget(){
    if(completeState==CompleteState::Ignore)return;//忽略光标和文本变化的响应,避免陷入事件死循环和互相钳制
    completeWidget->hide();
    completeState=CompleteState::Hide;
    QString word=this->getWordOfCursor();
    completeWidget->clear();
    if(!word.isEmpty()){//光标所在单词是不是合法(能不能联想)
        int maxSize=0;
        QMap<QString,int> distance;
        vector<QString> itemList;
        foreach(const QString &temp,completeList){
             if(temp.contains(word)){
              //completeWidget->addItem(new QListWidgetItem(temp));
                itemList.push_back(temp);
                distance[temp]=CompleteListWidget::ldistance(temp.toStdString(),word.toStdString());
                if(temp.length()>maxSize) maxSize=temp.length();
            }
        }
      //有没有匹配的字符
        if(itemList.size()>0){//如果有的话
            sort(itemList.begin(),itemList.end(),[&](const QString &s1,const QString &s2)->bool{return distance[s1]<distance[s2]; });
            foreach(const QString& item,itemList){
                completeWidget->addItem(new QListWidgetItem(item));
            }

            int x=this->getCompleteWidgetX();
            int y=this->cursorRect().y()+fontMetrics().height();

            completeWidget->move(x,y);
            if(completeWidget->count()>5) completeWidget->setFixedHeight(fontMetrics().height()*6);
            else completeWidget->setFixedHeight(fontMetrics().height()*(completeWidget->count()+1));
            completeWidget->setFixedWidth((fontMetrics().width(QLatin1Char('9'))+6)*maxSize);
            completeWidget->show();
            completeState=CompleteState::Showing;
            completeWidget->setCurrentRow(0,QItemSelectionModel::Select);
        }
    }

}

int EcodeEditor::getCompleteWidgetX(){
      QTextCursor cursor=this->textCursor();
      int pos=cursor.position()-1;
      int origianlPos=pos+1;
      QChar ch;
      ch=this->document()->characterAt(pos);
      while((ch.isDigit()||ch.isLetter()||ch=='_'||ch=='#')&&pos>0){
            pos--;
            ch=this->document()->characterAt(pos);
      }
      pos++;
      completeState=CompleteState::Ignore;
      cursor.setPosition(pos);
      this->setTextCursor(cursor);
      int x=this->cursorRect().x()+2*fontMetrics().width(QLatin1Char('9'));
      cursor.setPosition(origianlPos);
      this->setTextCursor(cursor);
      completeState=CompleteState::Hide;
      return x;
}

void EcodeEditor::setUpHighlighter()
{
    highlighter = new Highlighter(this->document());
}
