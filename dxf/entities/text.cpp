#include "text.h"

TEXT::TEXT()
{
}

void TEXT::draw() const
{
    qDebug(Q_FUNC_INFO);
}

void TEXT::parse(CodeData& code)
{
    //    do {
    //        data << code;
    //        code = nextCode();
    //    } while (code.code != 0);
    //    qDebug() << "TEXT" << data;
    //    code = DxfFile::ReadCodes(true);
}
