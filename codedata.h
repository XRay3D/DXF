#pragma once

#include <QObject>

struct CodeData {
    enum Type {
        String,
        Double,
        Integer
    };

    CodeData(int code = 0, const QString& val = {});

    /*const*/ int code = 0;
    Type type = String;

    quint64 iVal = std::numeric_limits<quint64>::min();
    QString sVal;
    /*const*/ QString rawVal;
    double dVal = -std::numeric_limits<double>::max();

    Q_ENUM(Type)
    Q_GADGET
};
