#pragma once

#include "../codedata.h"
#include <QDebug>
#include <QObject>
#include <QVector>

struct SectionParser {
public:
    explicit SectionParser(const QVector<CodeData>& data);
    virtual ~SectionParser() = default;
    virtual void parse() = 0;
    static int key(const QString& key);

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

    Q_GADGET
    Q_ENUM(sec)
};
