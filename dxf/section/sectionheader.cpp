#include "sectionheader.h"

#include <QTreeWidget>
#include <dxf/dxf.h>

SectionHEADER::SectionHEADER(DxfHeader& header, const QVector<CodeData>& data)
    : SectionParser(data)
    , header(header)
{
}

void SectionHEADER::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    QString key;
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = DxfFile::ReadCodes();
        data << code;
        if (code.rawVal.startsWith('$')) {
            key = code.rawVal;
        } else if (code.rawVal == "ENDSEC") {
            break;
        } else {
            switch (code.type) {
            case CodeData::String:
                header.data[key][code.code] = std::get<QString>(code._val);
                break;
            case CodeData::Double:
                header.data[key][code.code] = std::get<double>(code._val);
                break;
            case CodeData::Integer:
                header.data[key][code.code] = std::get<qint64>(code._val);
                break;
            }
        }
    }
    //    qDebug() << hData;
    //    qDebug() << hData.keys();
    if constexpr (0) {
        auto tw = new QTreeWidget();
        tw->setColumnCount(2);
        auto iPar = header.data.constBegin();
        QList<QTreeWidgetItem*> items;
        while (iPar != header.data.constEnd()) {
            items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(iPar.key())));
            {
                auto iVal = iPar.value().constBegin();
                while (iVal != iPar.value().constEnd()) {
                    items.last()->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList { QString::number(iVal.key()), iVal.value().toString() }));
                    ++iVal;
                }
            }
            ++iPar;
        }
        tw->insertTopLevelItems(0, items);
        tw->setWindowFlag(Qt::WindowStaysOnTopHint, true);
        tw->expandAll();
        tw->show();
    }
}
