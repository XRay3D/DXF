#include "sectionblocks.h"
#include <dxf/dxf.h>

SectionBLOCKS::SectionBLOCKS(const QVector<CodeData>& data)
    : SectionParser(data)
{
}

void SectionBLOCKS::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = DxfFile::ReadCodes();
        data << code;
        QString name;
        DxfBlock block;
        block << code;
        while (code.rawVal != "ENDBLK") {
            if (code.rawVal == "ENDSEC") {
                break;
            }
            code = DxfFile::ReadCodes();
            data << code;

            block << code;
            if ((code.code == 2 || code.code == 3) && name.isEmpty()) {
                name = code.rawVal;
            }
        }
        if (!name.isEmpty()) {
            blocks[name] = block;
        }
    }
    //    qDebug() << blocks.size();
    //    for (auto& b : blocks) {
    //        qDebug() << b.bData;
    //        qDebug() << b.data;
    //    }
}
