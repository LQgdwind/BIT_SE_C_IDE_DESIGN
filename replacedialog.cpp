#include "ReplaceDialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent,  QPlainTextEdit* pText) :
    FindDialog(parent, pText)
{
    initControl();
    connectSlot();
    setWindowTitle("Replace");
}

void ReplaceDialog::initControl()
{
    m_replaceLbl.setText("Replace To:");
    m_replaceBtn.setText("Replace");
    m_replaceAllBtn.setText("Replace All");

    m_layout.removeWidget(&m_matchChkBx); // 父类的构造函数已经初始化，所以需要移除
    m_layout.removeWidget(&m_radioGrpBx);
    m_layout.removeWidget(&m_closeBtn);

    m_layout.addWidget(&m_replaceLbl, 1, 0);
    m_layout.addWidget(&m_replaceEdit, 1, 1);
    m_layout.addWidget(&m_replaceBtn, 1, 2);
    m_layout.addWidget(&m_matchChkBx, 2, 0);
    m_layout.addWidget(&m_radioGrpBx, 2, 1);
    m_layout.addWidget(&m_replaceAllBtn, 2, 2);
    m_layout.addWidget(&m_closeBtn, 3, 2);
}

void ReplaceDialog::connectSlot()
{
    connect(&m_replaceBtn, SIGNAL(clicked()), this, SLOT(onReplaceClicked()));
    connect(&m_replaceAllBtn, SIGNAL(clicked()), this, SLOT(onReplaceAllClicked()));
}

void ReplaceDialog::onReplaceClicked()
{
    QString target = m_findEdit.text();
    QString to = m_replaceEdit.text();

    if( (m_pText != NULL) && (target != "") && (to != "") )
    {
        QString selText = m_pText->textCursor().selectedText();//第一次没有选择任何文本

        if( selText == target )
        {
            m_pText->insertPlainText(to);
        }

        onFindClicked();//第一次不会替换，会查找，符合Windows上的记事本替换准则
    }
}

void ReplaceDialog::onReplaceAllClicked()
{
    QString target = m_findEdit.text();
    QString to = m_replaceEdit.text();

    if( (m_pText != NULL) && (target != "") && (to != "") )
    {
        QString text = m_pText->toPlainText();

        text.replace(target, to, m_matchChkBx.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

        m_pText->clear();

        m_pText->insertPlainText(text);
    }
}
