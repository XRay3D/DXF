#include "ltype.h"

LTYPE::LTYPE(SectionParser* sp)
    : TableItem(sp)
{
}

void LTYPE::parse(CodeData& code)
{
    do {
        data << code;
        code = sp->nextCode();
    } while (code.code != 0);
//    code = sp->prevCode();
}
