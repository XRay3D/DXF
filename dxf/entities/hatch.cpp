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
    qDebug(Q_FUNC_INFO);
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
        }
    }
    scene->addPolygon(poly, QPen(QColor(0, 0, 0, 100), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QColor(255, 0, 0, 100));
}

void HATCH::drawInsert(INSERT_ET* i) const { Q_UNUSED(i) }

void HATCH::parse(CodeData& code)
{
    do {
        data << code;
        code = sp->nextCode();
    } while (code.code != 0);
    code = sp->prevCode();
}
