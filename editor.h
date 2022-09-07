#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include "eoutput.h"
#include "helper.h"
#include "efilebar.h"
#include "ecodeedit.h"

class Editor : public QWidget
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = nullptr);
    QVBoxLayout *layout;
    EfileBar *efilebar;
    EcodeEditor *OriginalEdit;
    EcodeEditor *edit;
    QLabel *eoutputlabel;
    EOutPut *eoutput;
    QFont getCurFont() const;
    void setCurFont(const QFont &value);
    QColor getCurColor() const;
    void setCurColor(const QColor &value);
private:
    QFont curFont{"Consolas [Cronyx]",15};
    QColor curColor{QColor(200,200,200)};
    void setupLayout();
    void updateEditLayout();
    void configureOriginalEdit();
    void removeTerminal();
    void addTerminal();
    void configureFontAndColor();
signals:
    void functionReferenceShouldChange(EcodeEditor *curEditor);
public slots:
    void handleUpdateEdit(EcodeEditor *newedit);
    void updateFunctionRef();
};

#endif // EDITOR_H
