#pragma once

#include "../codedata.h"
#include <QDebug>
#include <QObject>
#include <QVector>

struct SectionParser {
public:
    explicit SectionParser(QVector<CodeData>&& data);
    virtual ~SectionParser() = default;
    virtual void parse() = 0;
    static int key(const QString& key);
    mutable int counter = 0;

    const CodeData& nextCode() const { return data.at(counter++); }
    const CodeData& prevCode() const { return data.at(--counter); };

    friend QDebug operator<<(QDebug debug, const SectionParser& c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "\rSEC(" << c.type << ", " << c.data.size() << ')';
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

    const QVector<CodeData> data;
    const sec type;

    Q_GADGET
    Q_ENUM(sec)
};
