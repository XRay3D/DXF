#include "sectionparser.h"
#include "../dxf.h"
#include <QDebug>
#include <QMetaEnum>

SectionParser::SectionParser(QVector<CodeData>&& data)
    : data(std::move(data))
    , type(static_cast<sec>(key(this->data[1].rawVal)))
{
}

int SectionParser::key(const QString& key)
{
    return staticMetaObject.enumerator(0).keysToValue(key.toLocal8Bit().data());
}
