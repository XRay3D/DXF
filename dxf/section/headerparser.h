#pragma once

#include "sectionparser.h"
#include <header.h>

struct SectionHEADER final : SectionParser {
    SectionHEADER(Header& header, QVector<CodeData>&& data);
    virtual ~SectionHEADER() = default;
    // Section interface
    void parse() override;
    Header& header;
};
