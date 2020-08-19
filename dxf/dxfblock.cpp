#include "dxfblock.h"
#include "dxf.h"

#include <section/sectionentities.h>

DxfBlock::DxfBlock()
{
}

DxfBlock::~DxfBlock() { qDeleteAll(entities); }

void DxfBlock::parse(CodeData& code)
{ // Прочитать другую пару код / значение
    code = DxfFile::ReadCodes();
    code = DxfFile::ReadCodes();
    do {
        if (bs && code.code) {
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
        } else {
            bs = false;
            SectionENTITIES se(code);
            entities = se.entities;
            se.entities.clear();
        }
        code = DxfFile::ReadCodes();
        //        if (code.rawVal == "ENDSEC" || code.rawVal == "ENDBLK")
        //            break;
        //        if (code.rawVal == "BLOCK")
        //            continue;
    } while (code.rawVal != "ENDBLK");

    do {
        code = DxfFile::ReadCodes();
    } while (code.code != 0);

    code = DxfFile::ReadCodes(true);

    qDebug() << blockName << layerName << basePoint << flags << blockDescription;
    qDebug() << "data" << entities;
    qDebug("\n");
}
