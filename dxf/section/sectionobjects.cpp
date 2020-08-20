#include "sectionobjects.h"

SectionOBJECTS::SectionOBJECTS(QVector<CodeData>&& data)
    : SectionParser(std::move(data))
{
}
