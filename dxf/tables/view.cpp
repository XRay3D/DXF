#include "view.h"

VIEW::VIEW(SectionParser* sp)
    : TableItem(sp)
{
}

void VIEW::parse(CodeData& code)
{
    do {
        data << code;
        code = sp->nextCode();
    } while (code.code() != 0);
//    code = sp->prevCode();
}
