#pragma once

#include "section.h"

struct SectionTHUMBNAILIMAGE final : SectionParser {
    SectionTHUMBNAILIMAGE(const QVector<CodeData>& data);
    virtual ~SectionTHUMBNAILIMAGE() = default;
    // Section interface
    void parse() override {}
};
