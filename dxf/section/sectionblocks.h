#pragma once

#include "sectionparser.h"
#include <dxfblock.h>

///////////////////////////////////////
/// \brief The SectionBLOCKS struct
///
struct SectionBLOCKS final : SectionParser {
    SectionBLOCKS(const QVector<CodeData>& data);
    virtual ~SectionBLOCKS() = default;
    // Section interface
    void parse() override;
    QMap<QString, DxfBlock> blocks;
};
