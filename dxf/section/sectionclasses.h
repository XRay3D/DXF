#pragma once

#include "sectionparser.h"

struct SectionCLASSES final : SectionParser {
    SectionCLASSES(const QVector<CodeData>& data);
    virtual ~SectionCLASSES() = default;
    // Section interface
    void parse() override {}
};
