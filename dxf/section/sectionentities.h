#pragma once

#include "section.h"

#include <dxf/codedata.h>
#include <dxf/entities/entity.h>

///////////////////////////////////////
/// \brief The SectionENTITIES struct
///
struct SectionENTITIES final : SectionParser {
    SectionENTITIES(const QVector<CodeData>& data);
    SectionENTITIES(CodeData& code);

    virtual ~SectionENTITIES() { qDeleteAll(entities); }
    // Section interface
    void parse() override;

    QVector<Entity*> entities;
    std::map<Entity::Type, QVector<Entity*>> entitiesMap;

private:
    bool iParse(CodeData& code);
    CodeData code;
    Entity::Type key;
    bool dontSkip = true;
};
