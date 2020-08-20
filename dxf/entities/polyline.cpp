#include "polyline.h"
#include "insert.h"
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QPolygonF>
#include <dxf/dxf.h>

extern QGraphicsScene* scene;

POLYLINE::POLYLINE(SectionParser* sp)
    : Entity(sp)
{
}

void POLYLINE::draw() const
{
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
    scene->addPolygon(poly, QPen(QColor(0, 0, 0, 100), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
}

void POLYLINE::drawInsert(INSERT_ET* i) const
{
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
    for (int r = 0; r < i->rowCount; ++r) {
        for (int c = 0; c < i->colCount; ++c) {
            QPointF tr(r * i->rowSpacing, r * i->colSpacing);
            auto item = scene->addPolygon(poly, QPen(QColor(0, 255, 255, 100), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
            item->setPos(i->insPt + tr);
            item->setScale(i->scaleX /*, i->scaleY*/);
            item->setRotation(i->rotationAngle);
        }
    }
}

void POLYLINE::parse(CodeData& code)
{
    data << code;
    while (code.rawVal != "SEQEND") {
        // Прочитать другую пару код / значение
        code = sp->nextCode();
        data << code;
    }
}
