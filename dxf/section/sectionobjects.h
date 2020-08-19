#pragma once

#include "sectionparser.h"

struct SectionOBJECTS final : SectionParser {
    SectionOBJECTS(const QVector<CodeData>& data);
    virtual ~SectionOBJECTS() = default;
    // Section interface
    void parse() override {}
};
