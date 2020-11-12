#pragma once
#include "dxf/dxf.h"
#include "sectionparser.h"

struct TableItem;
struct LAYER;

struct SectionTABLES final : SectionParser {
    SectionTABLES(Layers& layers, QVector<CodeData>&& data);
    virtual ~SectionTABLES() = default;
    // Section interface
    void parse() override;
    QVector<QVector<TableItem*>> tables;
    Layers& layers;
};
