#pragma once

#include "section.h"

struct SectionHEADER final : SectionParser {
    SectionHEADER(DxfHeader& header, const QVector<CodeData>& data);
    virtual ~SectionHEADER() = default;
    // Section interface
    void parse() override;
    DxfHeader& header;
};
