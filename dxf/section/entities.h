#pragma once

#include "sectionparser.h"

#include <dxf/codedata.h>
#include <dxf/entities/entity.h>
#include <dxfblock.h>

///////////////////////////////////////
/// \brief The SectionENTITIES struct
///
struct SectionENTITIES final : SectionParser {
    explicit SectionENTITIES(QMap<QString, DxfBlock*>& blocks, QVector<CodeData>&& data);
    SectionENTITIES(QMap<QString, DxfBlock*>& blocks, CodeData& code, SectionParser* sp = nullptr);

    virtual ~SectionENTITIES() { qDeleteAll(entities); }
    // Section interface
    void parse() override;

    QVector<Entity*> entities;
    std::map<Entity::Type, QVector<Entity*>> entitiesMap;

private:
    void iParse(CodeData& code);
    CodeData code;
    Entity::Type key;
    SectionParser* sp;
    QMap<QString, DxfBlock*>& blocks;
};
