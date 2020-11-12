#include "entity.h"
#include <QMetaEnum>
#include <dxf/dxf.h>
#include <tables/layer.h>

Entity::Entity(SectionParser* sp)
    : sp(sp)
{
}

Entity::Type Entity::TypeVal(const QString& key)
{
    return static_cast<Type>(staticMetaObject.enumerator(0).keyToValue(key.toLocal8Bit().toUpper().data()));
}

QString Entity::TypeName(int key) { return staticMetaObject.enumerator(0).valueToKey(key); }

void Entity::parseEntity(CodeData& code)
{
    switch (code.code()) {
    case LayerName:
        layerName = code;
        break;
    case Handle:
        handle = code;
        break;
    default:
        break;
    }
}

QColor Entity::color() const
{
    if (auto layer = DxfFile::layer(layerName); layer != nullptr) {
        QColor c(dxfColors[layer->colorNumber]);
        c.setAlpha(200);
        return c;
    }
    qDebug(Q_FUNC_INFO);
    return QColor(255, 0, 255, 100);
}

void Entity::attachToLayer(QGraphicsItem* item) const
{
    if (DxfFile::layer(layerName)) {
        DxfFile::layer(layerName)->gig->addToGroup(item);
        item->setToolTip(TypeName(type()));
    }
}
