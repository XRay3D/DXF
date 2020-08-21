#include "tables.h"
#include <dxf/dxf.h>

#include <tables/tableitem.h>

SectionTABLES::SectionTABLES(QMap<QString, LAYER*>& layers, QVector<CodeData>&& data)
    : SectionParser(std::move(data))
    , layers(layers)
{
}

void SectionTABLES::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    code = nextCode();
    code = nextCode();
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = nextCode();
        qDebug() << "TABLE" << code;
        if (code.rawVal == "TABLE") {
            tables.resize(tables.size() + 1);
            code = nextCode();
            do {
                switch (TableItem::toType(code.rawVal)) {
                case TableItem::APPID:
                    tables.last().append(new APPID(this));
                    tables.last().last()->parse(code);
                    break;
                case TableItem::BLOCK_RECORD:
                    tables.last().append(new BLOCK_RECORD(this));
                    tables.last().last()->parse(code);
                    break;
                case TableItem::DIMSTYLE:
                    tables.last().append(new DIMSTYLE(this));
                    tables.last().last()->parse(code);
                    break;
                case TableItem::LAYER:
                    LAYER* l;
                    tables.last().append(l = new LAYER(this));
                    tables.last().last()->parse(code);
                    layers[l->name] = l;
                    continue;
                case TableItem::LTYPE:
                    tables.last().append(new LTYPE(this));
                    tables.last().last()->parse(code);
                    break;
                case TableItem::STYLE:
                    tables.last().append(new STYLE(this));
                    tables.last().last()->parse(code);
                    break;
                case TableItem::UCS:
                    tables.last().append(new UCS(this));
                    tables.last().last()->parse(code);
                    break;
                case TableItem::VIEW:
                    tables.last().append(new VIEW(this));
                    tables.last().last()->parse(code);
                    break;
                case TableItem::VPORT:
                    tables.last().append(new VPORT(this));
                    tables.last().last()->parse(code);
                    break;
                }
            } while (code.rawVal != "ENDTAB");
        }
    }
    qDebug() << tables.size();
    for (auto t : tables) {
        qDebug() << t.size() << t;
    }
}
