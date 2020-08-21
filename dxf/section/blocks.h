#pragma once

#include "sectionparser.h"
#include <block.h>

///////////////////////////////////////
/// \brief The SectionBLOCKS struct
///
struct SectionBLOCKS final : SectionParser {
    SectionBLOCKS(QMap<QString, Block*>& blocks, QVector<CodeData>&& data);
    virtual ~SectionBLOCKS() = default;
    // Section interface
    void parse() override;
    QMap<QString, Block*>& blocks;
};
