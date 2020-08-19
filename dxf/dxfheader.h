#pragma once

#include <QMap>
#include <QVariant>

struct DxfHeader {
    DxfHeader();
    QMap<QString, QMap<int, QVariant>> data;
};
