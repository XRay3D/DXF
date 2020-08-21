#pragma once
#include "sectionparser.h"

struct TableItem;
struct LAYER;

struct SectionTABLES final : SectionParser {
    SectionTABLES(QMap<QString, LAYER*> &layers,QVector<CodeData>&& data);
    virtual ~SectionTABLES() = default;
    // Section interface
    void parse() override;
    QVector<QVector<TableItem*>> tables;
    QMap<QString, LAYER*> &layers;
};
