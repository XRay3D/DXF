#pragma once

#include "sectionparser.h"
#include <dxfheader.h>

struct SectionHEADER final : SectionParser {
    SectionHEADER(DxfHeader& header, QVector<CodeData>&& data);
    virtual ~SectionHEADER() = default;
    // Section interface
    void parse() override;
    DxfHeader& header;
};
