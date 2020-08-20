#include "header.h"

#include <QTreeWidget>
#include <dxf/dxf.h>

SectionHEADER::SectionHEADER(DxfHeader& header, QVector<CodeData>&& data)
    : SectionParser(std::move(data))
    , header(header)
{
}

void SectionHEADER::parse()
{
    CodeData code;
    QString key;
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = nextCode();
        if (code.rawVal.startsWith('$')) {
            key = code.rawVal;
        } else if (code.rawVal == "ENDSEC") {
            break;
        } else if (!key.isEmpty()) {
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
    if constexpr (0) {
        auto tw = new QTreeWidget();
        tw->setWindowTitle("Section HEADER");
        tw->setColumnCount(2);
        auto iPar = header.data.constBegin();
        QList<QTreeWidgetItem*> items;
        while (iPar != header.data.constEnd()) {
            items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(iPar.key())));
            {
                auto iVal = iPar.value().constBegin();
                while (iVal != iPar.value().constEnd()) {
                    items.last()->addChild(new QTreeWidgetItem(static_cast<QTreeWidget*>(nullptr), { QString::number(iVal.key()), iVal.value().toString() }));
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
