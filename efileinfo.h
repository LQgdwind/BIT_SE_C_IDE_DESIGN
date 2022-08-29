#ifndef EFILEINFO_H
#define EFILEINFO_H
#include "efilelabel.h"
#include "ecodeedit.h"

class EFileInfo
{
public:
    EFileLabel *label;
    EcodeEditor *edit;
    EFileInfo();
    EFileInfo(EFileLabel *label,EcodeEditor *edit);
};

#endif // EFILEINFO_H
