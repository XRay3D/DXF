#include "entity.h"
#include <QMetaEnum>
#include <dxf/dxf.h>
#include <tables/layer.h>

Entity::Entity(SectionParser* sp)
    : sp(sp)
{
}

int Entity::toType(const QString& key)
{
    return staticMetaObject.enumerator(0).keyToValue(key.toLocal8Bit().toUpper().data());
}

void Entity::parseEntity(CodeData& code)
{
    switch (code.code) {
    case LayerName:
        layerName = code.getString();
        break;
    default:
        break;
    }
}

QColor Entity::color() const
{
    if (DxfFile::layer(layerName))
        return dxfColors[DxfFile::layer(layerName)->colorNumber];
    return QColor(0, 0, 0, 50);
}

void Entity::attachToLayer(QGraphicsItem* item) const
{
    if (DxfFile::layer(layerName))
        DxfFile::layer(layerName)->gig->addToGroup(item);
}
