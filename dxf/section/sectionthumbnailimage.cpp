#include "sectionthumbnailimage.h"

SectionTHUMBNAILIMAGE::SectionTHUMBNAILIMAGE(QVector<CodeData>&& data)
    : SectionParser(std::move(data))
{
}
