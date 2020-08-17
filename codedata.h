#pragma once

#include <QDebug>
#include <QObject>

struct CodeData {

    friend QDebug operator<<(QDebug debug, const CodeData& c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "DC(" << c.code << ", " << c.rawVal << /* ", " << c.type << */ ')';
        return debug;
    }

    enum Type {
        String,
        Double,
        Integer
    };

    CodeData(int code = 0, const QString& val = {});

    int code = 0;
    Type type = String;
    std::variant<qint64, QString, double> _val;
    QString rawVal;

    Q_ENUM(Type)
    Q_GADGET
};
