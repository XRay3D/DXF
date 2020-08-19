#include "section.h"
#include "../dxf.h"
#include <QDebug>

SectionParser::SectionParser(const QVector<CodeData>& data)
    : type(static_cast<sec>(key(data.last().rawVal)))
    , data(data)
{
}
