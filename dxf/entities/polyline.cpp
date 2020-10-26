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

void POLYLINE::draw(const INSERT_ET* const i) const
{
    QPolygonF poly;
    QPointF pt;
    double width = 0;
    double width2 = 0;
    for (auto& d : data) {
        if (d.code() == 10) {
            pt.rx() = d;
        } else if (d.code() == 20) {
            pt.ry() = d;
            poly.append(pt);
        } else if (d.code() == 11) {
            pt.rx() = d;
        } else if (d.code() == 21) {
            pt.ry() = d;

            poly.append(pt);
        } else if (d.code() == 40) {
            width = d;
        } else if (d.code() == 41) {
            width2 = d;
        }
    }

    if (i) {
        for (int r = 0; r < i->rowCount; ++r) {
            for (int c = 0; c < i->colCount; ++c) {
                QPointF tr(r * i->rowSpacing, r * i->colSpacing);
                auto item = scene->addPolygon(poly, QPen(i->color(), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
                item->setToolTip(layerName);
                i->transform(item, tr);
                i->attachToLayer(item);
                qDebug() << item->boundingRect().size().width() << item->boundingRect().size().height() << width << width2;
            }
        }
        //qDebug() << "POLYLINE" << data;
    } else {
        attachToLayer(scene->addPolygon(poly, QPen(color(), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush));
    }
}

void POLYLINE::parse(CodeData& code)
{
    data << code;
    do {
        // Прочитать другую пару код / значение
        data << (code = sp->nextCode());
        parseEntity(code);
    } while (code != "SEQEND");
    do {
        // Прочитать другую пару код / значение
        data << (code = sp->nextCode());
        parseEntity(code);
    } while (code.code() != 0);
}
