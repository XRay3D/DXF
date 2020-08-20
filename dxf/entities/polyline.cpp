#include "polyline.h"
#include <QGraphicsScene>
#include <QPolygonF>
#include <dxf/dxf.h>

extern QGraphicsScene* scene;

POLYLINE::POLYLINE()
{
}

void POLYLINE::draw() const
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
            poly.append(pt);
        } else if (d.code == 11) {
            pt.rx() = std::get<double>(d._val);
        } else if (d.code == 21) {
            pt.ry() = std::get<double>(d._val);
            poly.append(pt);
        } else if (d.code == 40) {
            width = std::get<double>(d._val);
        }
    }
    scene->addPolygon(poly, QPen(Qt::black, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
}

void POLYLINE::parse(CodeData& code)
{
    //    data << code;
    //    while (code.rawVal != "SEQEND") {
    //        // Прочитать другую пару код / значение
    //        code = nextCode();
    //        data << code;
    //    }
}
