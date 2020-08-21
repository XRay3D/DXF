#pragma once

#include <QMap>
#include <QVariant>

struct Header {
    Header();
    QMap<QString, QMap<int, QVariant>> data;
};
