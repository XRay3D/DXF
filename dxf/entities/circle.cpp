#include "circle.h"

#include <dxf.h>

CIRCLE::CIRCLE()
{
}

void CIRCLE::draw() const
{
}

void CIRCLE::parse(CodeData& code)
{
    do {
        data << code;
        switch (static_cast<VarType>(code.code)) {
        case SubclassMarker:
            break;
        case Thickness:
            thickness = code.getDouble();
            break;
        case CenterPointX:
            centerPoint.rx() = code.getDouble();
            break;
        case CenterPointY:
            centerPoint.ry() = code.getDouble();
            break;
        case CenterPointZ:
            break;
        case Radius:
            radius = code.getDouble();
            break;
        case ExtrDirX:
            break;
        case ExtrDirY:
            break;
        case ExtrDirZ:
            break;
        }
        code = DxfFile::ReadCodes();
    } while (code.code != 0);
    code = DxfFile::ReadCodes(true);
}
