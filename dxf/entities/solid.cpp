#include "solid.h"

#include <dxf.h>

SOLID::SOLID()
{
}

void SOLID::draw() const
{    qDebug(Q_FUNC_INFO);

}

void SOLID::parse(CodeData& code)
{
    do {
        data << code;
        switch (static_cast<VarType>(code.code)) {
        case SubclassMarker:
            break;
        case Thickness:
            thickness = code.getDouble();
            break;
        case FirstCornerX:
            firstCorner.rx() = code.getDouble();
            corners << FirstCornerX;
            break;
        case FirstCornerY:
            firstCorner.ry() = code.getDouble();
            break;
        case FirstCornerZ:
            break;
        case SecondCornerX:
            secondCorner.rx() = code.getDouble();
            corners << SecondCornerX;
            break;
        case SecondCornerY:
            secondCorner.ry() = code.getDouble();
            break;
        case SecondCornerZ:
            break;
        case ThirdCornerX:
            thirdCorner.rx() = code.getDouble();
            corners << ThirdCornerX;
            break;
        case ThirdCornerY:
            thirdCorner.ry() = code.getDouble();
            break;
        case ThirdCornerZ:
            break;
        case FourthCornerX:
            fourthCorner.rx() = code.getDouble();
            corners << FourthCornerX;
            break;
        case FourthCornerY:
            fourthCorner.ry() = code.getDouble();
            break;
        case FourthCornerZ:
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
