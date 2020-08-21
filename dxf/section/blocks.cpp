#include "blocks.h"
#include <dxf/dxf.h>

SectionBLOCKS::SectionBLOCKS(QMap<QString, Block*>& blocks, QVector<CodeData>&& data)
    : SectionParser(std::move(data))
    , blocks(blocks)
{
}

void SectionBLOCKS::parse()
{
    CodeData code;
    while (code.rawVal != "ENDSEC") {
        code = nextCode();
        if (code.rawVal == "BLOCK") {
            auto block = new Block(blocks, this);
            block->parse(code);
            if (!block->blockName.isEmpty()) {
                blocks[block->blockName] = block;
            } else {
                delete block;
            }
        }
    }
}
