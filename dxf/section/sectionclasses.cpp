#include "sectionclasses.h"

SectionCLASSES::SectionCLASSES(QVector<CodeData>&& data)
    : SectionParser(std::move(data))
{
}
