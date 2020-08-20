#include "tables.h"
#include <dxf/dxf.h>

SectionTABLES::SectionTABLES(QVector<CodeData>&& data)
    : SectionParser(std::move(data))
{
}

void SectionTABLES::parse()
{
    //    qDebug(Q_FUNC_INFO);
    //    CodeData code;
    //    while (code.rawVal != "ENDSEC") {
    //        // Прочитать другую пару код / значение
    //        code = nextCode();
    //        data << code;

    //        if (code.rawVal == "TABLE") {
    //            tables.resize(tables.size() + 1);
    //        } else if (code.rawVal == "ENDSEC") {
    //            break;
    //        }
    //        tables.last().append(code);
    //    }
    //    //    qDebug() << tables.size();
}
