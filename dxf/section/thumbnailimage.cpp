#include "thumbnailimage.h"

SectionTHUMBNAILIMAGE::SectionTHUMBNAILIMAGE(QVector<CodeData>&& data)
    : SectionParser(std::move(data))
{
}
