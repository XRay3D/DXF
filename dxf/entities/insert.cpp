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
        if (auto key = static_cast<VarType>(code.code); checker.count(key))
            vars.emplace(key, code._val);
        code = DxfFile::ReadCodes();
    } while (code.code != 0);
}
