#include "dxfblock.h"
#include "dxf.h"

#include <section/entities.h>

DxfBlock::DxfBlock(QMap<QString, DxfBlock*>& blocks, SectionParser* sp)
    : sp(sp)
    , blocks(blocks)
{
}

DxfBlock::~DxfBlock()
{ /*qDeleteAll(entities);*/
}

void DxfBlock::parse(CodeData& code)
{
    parseHeader(code);
    parseData(code);
    do {
        code = sp->nextCode();
    } while (code.code != 0);
    code = sp->prevCode();
}

void DxfBlock::parseHeader(CodeData& code)
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
}

void DxfBlock::parseData(CodeData& code)
{
    do {
        if (code.rawVal == "ENDBLK")
            break;
        SectionENTITIES se(blocks, code, sp);
        entities = se.entities;
        se.entities.clear();
        if (code.rawVal == "ENDBLK")
            break;
        code = sp->nextCode();
    } while (code.rawVal != "ENDBLK");
}
