#include "entity.h"
#include <QMetaEnum>
#include <dxf/dxf.h>
#include <tables/layer.h>

Entity::Entity(SectionParser* sp)
    : sp(sp)
{
}

int Entity::toType(const QString& key) { return staticMetaObject.enumerator(0).keyToValue(key.toLocal8Bit().toUpper().data()); }

QString Entity::toType(int key) { return staticMetaObject.enumerator(0).valueToKey(key); }

void Entity::parseEntity(CodeData& code)
{
    switch (code.code()) {
    case LayerName:
        layerName = QString(code);
        break;
    default:
        break;
    }
}

QColor Entity::color() const
{
    if (auto layer = DxfFile::layer(layerName); layer) {
        QColor c(dxfColors[layer->colorNumber]);
        return c;
    }
    qDebug(Q_FUNC_INFO);
    return QColor(255, 0, 255, 100);
}

void Entity::attachToLayer(QGraphicsItem* item) const
{
    if (DxfFile::layer(layerName)) {
        DxfFile::layer(layerName)->gig->addToGroup(item);
        item->setToolTip(toType(type()));
    }
}
