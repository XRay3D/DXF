#include "insert.h"

#include <dxf/dxf.h>

INSERT::INSERT()
    : checker {
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
{
}

void INSERT::draw() const
{
}

void INSERT::parse(CodeData& code)
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
                break;
            case ColCount:
                break;
            case RowCount:
                break;
            case ColSpacing:
                break;
            case RowSpacing:
                break;
            case ExtrDirX:
                break;
            case ExtrDirY:
                break;
            case ExtrDirZ:
                break;
            }
        }

        code = DxfFile::ReadCodes();
    } while (code.code != 0);
}
