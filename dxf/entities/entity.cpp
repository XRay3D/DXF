#include "entity.h"

#include <QMetaEnum>

Entity::Entity()
{
}

int Entity::toType(const QString& key)
{
    return staticMetaObject.enumerator(0).keyToValue(key.toLocal8Bit().toUpper().data());
}
