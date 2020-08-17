#include "codedata.h"

CodeData::CodeData(int code, const QString& val)
    : code(code)
    , type(String)
    , rawVal(val)
{
    if (0 <= code && code <= 9) { //  0 — 9  Строковое
        type = String;
        sVal = val;
    } else if (10 <= code && code <= 59) { // 10 — 59 С плавающей точкой
        type = Double;
        dVal = val.toDouble();
    } else if (60 <= code && code <= 79) { // 60 — 79 Целое
        type = Integer;
        iVal = val.toLongLong();
    }
}
