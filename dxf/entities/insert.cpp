#include "insert.h"

#include <dxf/dxf.h>

INSERT_ET::INSERT_ET(QMap<QString, DxfBlock*>& blocks, SectionParser* sp)
    : Entity(sp)

    , checker {
        SubclassMrker,
        var66,
        BlockName,
        InsPtX,
        InsPtY,
        InsPtZ,
        ScaleX,
        ScaleY,
        ScaleZ,
        RotationAngle,
        ColCount,
        RowCount,
        ColSpacing,
        RowSpacing,
        ExtrDirX,
        ExtrDirY,
        ExtrDirZ
    }
    , blocks(blocks)
{
}

void INSERT_ET::draw() const
{
    if (blocks.contains(blockName))
        for (auto e : blocks[blockName]->entities) {
            e->drawInsert(const_cast<INSERT_ET*>(this));
        }
}

void INSERT_ET::drawInsert(INSERT_ET* i) const
{
    if (blocks.contains(blockName))
        for (auto e : blocks[blockName]->entities) {
            e->drawInsert(const_cast<INSERT_ET*>(i));
        }
}

void INSERT_ET::parse(CodeData& code)
{
    do {
        data << code;
        if (auto key = static_cast<VarType>(code.code); checker.count(key)) {
            vars.emplace(key, code._val);
            switch (key) {
            case SubclassMrker:
                break;
            case var66:
                break;
            case BlockName:
                blockName = code.getString();
                break;
            case InsPtX:
                insPt.rx() = code.getDouble();
                break;
            case InsPtY:
                insPt.ry() = code.getDouble();
                break;
            case InsPtZ:
                break;
            case ScaleX:
                scaleX = code.getDouble();
                break;
            case ScaleY:
                scaleY = code.getDouble();
                break;
            case ScaleZ:
                break;
            case RotationAngle:
                rotationAngle = code.getDouble();
                break;
            case ColCount:
                colCount = code.getInteger();
                break;
            case RowCount:
                rowCount = code.getInteger();
                break;
            case ColSpacing:
                colSpacing = code.getDouble();
                break;
            case RowSpacing:
                rowSpacing = code.getDouble();
                break;
            case ExtrDirX:
                break;
            case ExtrDirY:
                break;
            case ExtrDirZ:
                break;
            }
        }
        code = sp->nextCode();
    } while (code.code != 0);
    code = sp->prevCode();
}
