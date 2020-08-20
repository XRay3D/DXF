#pragma once
#include "sectionparser.h"

struct SectionTABLES final : SectionParser {
    SectionTABLES(QVector<CodeData>&& data);
    virtual ~SectionTABLES() = default;
    // Section interface
    void parse() override;
    QVector<QVector<CodeData>> tables;
};
