#pragma once

#include <QDebug>
#include <QObject>

using var = std::variant<double, qint64, QString>;

struct CodeData {

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

    CodeData(int code = 0, const QString& val = {});

    double getDouble() { return std::get<Double>(_val); }
    qint64 getInteger() { return std::get<Integer>(_val); }
    QString getString() { return std::get<String>(_val); }

    int code = 0;
    Type type = String;
    var _val;
    QString rawVal;

    Q_ENUM(Type)
    Q_GADGET
};
