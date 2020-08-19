#include "dxfblock.h"
#include "dxf.h"

#include <section/sectionentities.h>

DxfBlock::DxfBlock()
{
}

void DxfBlock::parse(CodeData& code)
{ // Прочитать другую пару код / значение
    do {
        code = DxfFile::ReadCodes();
        if (code.rawVal == "ENDSEC" || code.rawVal == "ENDBLK")
            break;
        if (code.rawVal == "BLOCK")
            continue;

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
    } while (code.rawVal != "ENDBLK");
    qDebug() << blockName << layerName << basePoint << flags << blockDescription;
    qDebug() << "data" << entities;
    qDebug("\n");
}
