#include "blocks.h"
#include <dxf/dxf.h>

SectionBLOCKS::SectionBLOCKS(QMap<QString, DxfBlock*>& blocks, QVector<CodeData>&& data)
    : SectionParser(std::move(data))
    , blocks(blocks)
{
}

void SectionBLOCKS::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    while (code.rawVal != "ENDSEC") {
        code = nextCode();
        if (code.rawVal == "BLOCK") {
            auto block = new DxfBlock(blocks, this);
            block->parse(code);
            if (!block->blockName.isEmpty()) {
                blocks[block->blockName] = block;
            }
        }
    }
}
