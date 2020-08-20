#include "dxfblock.h"
#include "dxf.h"

#include <section/sectionentities.h>

DxfBlock::DxfBlock(SectionParser* sp)
    : sp(sp)
{
}

DxfBlock::~DxfBlock() { qDeleteAll(entities); }

void DxfBlock::parse(CodeData& code)
{
    do { // Block header
        bData.append(code);
        switch (code.code) {
        case EntityType:
            break;
        case Handle:
            break;
            //            case StartOfApplication_definedGroup:
            //                break;
            //            case EndOfGroup:
            //                break;
        case SoftPointerID:
            break;
        case SubclassMarker:
            break;
        case LayerName:
            layerName = code.rawVal;
            break;
            //            case SubclassMarker_2:
            //                break;
        case BlockName:
            blockName = code.rawVal;
            break;
        case BlockTypeFlags:
            flags = static_cast<BTFlags>(code.getInteger());
            break;
        case BasePointX:
            basePoint.rx() = code.getDouble();
            break;
        case BasePointY:
            basePoint.ry() = code.getDouble();
            break;
        case BasePointZ:
            break;
        case BlockName_2:
            blockName = code.rawVal;
            break;
        case XrefPathName:
            break;
        case BlockDescription:
            blockDescription = code.rawVal;
            break;
        }
        code = sp->nextCode();
    } while (code.code != 0);
    // Прочитать другую пару код / значение
    //    code = nextCode();
    //    //code = nextCode();
    do {

        bs = false;
        SectionENTITIES se(code);
        entities = se.entities;
        se.entities.clear();
        if (code.rawVal != "ENDBLK")
            break;

        code = sp->nextCode();
    } while (code.rawVal != "ENDBLK");

    do {
        code = sp->nextCode();
    } while (code.code != 0);

    code = sp->prevCode();
}
