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
        code = DxfFile::ReadCodes();
        //        DxfBlock block;
        //        block.parse(code);
        //        qDebug() << "blockName" << block.blockName;
        //        if (!block.blockName.isEmpty()) {
        //            blocks[block.blockName] = block;
        //        }
    }
}
