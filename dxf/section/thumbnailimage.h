#pragma once

#include "sectionparser.h"

struct SectionTHUMBNAILIMAGE final : SectionParser {
    SectionTHUMBNAILIMAGE(QVector<CodeData>&& data);
    virtual ~SectionTHUMBNAILIMAGE() = default;
    // Section interface
    void parse() override {}
};
