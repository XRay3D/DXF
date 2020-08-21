#include "appid.h"

APPID::APPID(SectionParser* sp)
    : TableItem(sp)
{
}

void APPID::parse(CodeData& code)
{
    do {
        data << code;
        code = sp->nextCode();
        switch (code.code) {
        case SubclassMarker:
            break;
        case ApplicationName:
            applicationName = code.getString();
            break;
        case StandardFlag:
            standardFlag = code.getInteger();
            break;
        }
    } while (code.code != 0);
//    code = sp->prevCode();
    qDebug() << "APPID(" << applicationName << standardFlag << ")";
}
