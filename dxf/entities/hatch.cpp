#include "hatch.h"
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QPolygonF>
#include <dxf/dxf.h>

extern QGraphicsScene* scene;

HATCH::HATCH(SectionParser* sp)
    : Entity(sp)
{
}

void HATCH::draw() const
{
    QPainterPath path;
    QPolygonF poly;
    QPointF pt;
    double width = 0;
    for (auto& d : data) {
        if (d.code == 10) {
            pt.rx() = std::get<double>(d._val);
        } else if (d.code == 20) {
            pt.ry() = std::get<double>(d._val);
            if (!pt.isNull())
                poly.append(pt);
        } else if (d.code == 11) {
            pt.rx() = std::get<double>(d._val);
        } else if (d.code == 21) {
            pt.ry() = std::get<double>(d._val);
            if (!pt.isNull())
                poly.append(pt);
        } else if (d.code == 40) {
            width = std::get<double>(d._val);
        } else if (d.code == 92) {
            path.addPolygon(poly);
            poly.clear();
        }
    }
    path.addPolygon(poly);
    attachToLayer(scene->addPath(path, QPen(color(), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), color()));
}

void HATCH::drawInsert(INSERT_ET* i) const
{
    return;
    Q_UNUSED(i)
}

void HATCH::parse(CodeData& code)
{
    do {
        data << code;
        code = sp->nextCode();
        parseEntity(code);
    } while (code.code != 0);
}
