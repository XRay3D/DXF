#include "classes.h"

SectionCLASSES::SectionCLASSES(QVector<CodeData>&& data)
    : SectionParser(std::move(data))
{
}
