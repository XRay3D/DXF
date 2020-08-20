#include "sectionblocks.h"
#include <dxf/dxf.h>

SectionBLOCKS::SectionBLOCKS(QVector<CodeData>&& data)
    : SectionParser(std::move(data))
{
}

void SectionBLOCKS::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    while (code.rawVal != "ENDSEC") {
        code = nextCode();
        if (code.rawVal == "BLOCK") {
            DxfBlock block(this);
            block.parse(code);
            qDebug() << "blockName" << block.blockName;
            if (!block.blockName.isEmpty()) {
                blocks[block.blockName] = block;
            }
        }
    }
}
