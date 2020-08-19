#include "hatch.h"

#include <dxf.h>

HATCH::HATCH()
{
}

void HATCH::draw() const
{
    qDebug(Q_FUNC_INFO);
}

void HATCH::parse(CodeData& code)
{
    do {
        data << code;
        qDebug() << "TEXT" << code;
        code = DxfFile::ReadCodes();
    } while (code.code != 0);
    code = DxfFile::ReadCodes(true);
}
