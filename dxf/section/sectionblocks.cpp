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
        DxfBlock block;
        block.parse(code);
        if (!block.blockName.isEmpty()) {
            blocks[block.blockName] = block;
        }
    }
}
