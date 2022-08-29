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
private:
    void setupLayout();
    void updateEditLayout();
    void configureOriginalEdit();
    void removeTerminal();
    void addTerminal();
signals:

public slots:
    void handleUpdateEdit(EcodeEditor *newedit);
};

#endif // EDITOR_H
