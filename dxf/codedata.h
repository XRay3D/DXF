#pragma once

#include <QDebug>
#include <QObject>

using var = std::variant<double, qint64, QString>;

struct CodeData {
    CodeData(int code = 0, const QString& val = {});

    friend QDebug operator<<(QDebug debug, const CodeData& c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "DC(" << c.code << ", " << c.rawVal << /* ", " << c.type << */ ')';
        return debug;
    }

    enum Type {
        Double,
        Integer,
        String,
    };

    double getDouble() const;
    qint64 getInteger() const;
    QString getString() const;

    int code = 0;
    Type type = String;
    var _val;
    QString rawVal;

    Q_ENUM(Type)
    Q_GADGET
};
