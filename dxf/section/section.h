#pragma once

#include "../codedata.h"
#include "../dxfblock.h"
#include "../dxfheader.h"
#include <QDebug>
#include <QObject>
#include <QVector>

struct SectionParser {
    friend QDebug operator<<(QDebug debug, const SectionParser& c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "\rSEC(" << c.type << ')';
        return debug;
    }

    enum sec {
        Null,
        HEADER,
        CLASSES,
        TABLES,
        BLOCKS,
        ENTITIES,
        OBJECTS,
        THUMBNAILIMAGE,
    };
    const sec type;
    QVector<CodeData> data;
    static int key(const QString& key);
    SectionParser(const QVector<CodeData>& data);
    virtual ~SectionParser() = default;
    virtual void parse() = 0;

    Q_GADGET
    Q_ENUM(sec)
};
