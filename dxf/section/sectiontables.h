#pragma once
#include "section.h"

struct SectionTABLES final : SectionParser {
    SectionTABLES(const QVector<CodeData>& data);
    virtual ~SectionTABLES() = default;
    // Section interface
    void parse() override;
    QVector<QVector<CodeData>> tables;
};