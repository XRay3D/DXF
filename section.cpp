#include "section.h"
#include "dxf.h"
#include <QDebug>
#include <QTreeWidget>

Section::Section(const QVector<CodeData>& data)
    : type(static_cast<sec>(key(data.last().rawVal)))
    , data(data)
{
}

void SectionHEADER::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    QString key;
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = DXF::ReadCodes();
        data << code;
        if (code.rawVal.startsWith('$')) {
            key = code.rawVal;
        } else if (code.rawVal == "ENDSEC") {
            break;
        } else {
            switch (code.type) {
            case CodeData::String:
                hData[key][code.code] = std::get<QString>(code._val);
                break;
            case CodeData::Double:
                hData[key][code.code] = std::get<double>(code._val);
                break;
            case CodeData::Integer:
                hData[key][code.code] = std::get<qint64>(code._val);
                break;
            }
        }
    }
    qDebug() << hData;
    qDebug() << hData.keys();
    if constexpr (0) {
        auto tw = new QTreeWidget();
        tw->setColumnCount(2);
        auto iPar = hData.constBegin();
        QList<QTreeWidgetItem*> items;
        while (iPar != hData.constEnd()) {
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

void SectionTABLES::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = DXF::ReadCodes();
        data << code;

        if (code.rawVal == "TABLE") {
            tables.resize(tables.size() + 1);
        } else if (code.rawVal == "ENDSEC") {
            break;
        }
        tables.last().append(code);
    }
    qDebug() << tables.size();
}

void SectionBLOCKS::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = DXF::ReadCodes();
        data << code;
        QString name;
        DxfBlock block;
        block << code;
        while (code.rawVal != "ENDBLK") {
            if (code.rawVal == "ENDSEC") {
                break;
            }
            code = DXF::ReadCodes();
            data << code;

            block << code;
            if ((code.code == 2 || code.code == 3) && name.isEmpty()) {
                name = code.rawVal;
            }
        }
        if (!name.isEmpty()) {
            blocks[name] = block;
        }
    }
    qDebug() << blocks.size();
    for (auto& b : blocks) {
        qDebug() << b.bData;
        qDebug() << b.data;
    }
}
