#include "lwpolyline.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QPainterPath>
#include <QPolygonF>
#include <dxf/dxf.h>

extern QGraphicsScene* scene;

LWPOLYLINE::LWPOLYLINE(SectionParser* sp)
    : Entity(sp)
{
}

void LWPOLYLINE::draw() const
{
    //    qDebug(Q_FUNC_INFO);
    //QPen p(QColor(0, 0, 0, 100), constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen p(QColor(0, 255, 255, 100), 0.0);
    if (bulge != 0.0) {

        QLineF l1(poly.first(), poly.last());
        double d = l1.length() * 0.5;
        double h = d * bulge;
        double r = (h * h + d * d) / (h * 2);
        QLineF l2(l1.center(), poly.last());
        QLineF n(l2.normalVector());
        n.setLength(h);

        QPointF a(poly.first());
        QPointF b(poly.last());
        QPointF c(n.p2());

        {
            QPointF o;
            double ax2 = a.x() * a.x();
            double bx2 = b.x() * b.x();
            double cx2 = c.x() * c.x();

            double ay2 = a.y() * a.y();
            double by2 = b.y() * b.y();
            double cy2 = c.y() * c.y();
            double D = a.x() * b.y() + a.y() * c.x() - b.y() * c.x() - a.x() * c.y() - b.x() * a.y() + b.x() * c.y();

            o.rx() = +0.5 / D * ( //
                         +a.y() * cx2 + a.y() * cy2 + b.y() * ax2 + b.y() * ay2 + c.y() * bx2 + c.y() * by2 //
                         - a.y() * bx2 - a.y() * by2 - b.y() * cx2 - b.y() * cy2 - c.y() * ax2 - c.y() * ay2);
            o.ry() = -0.5 / D * ( //
                         +a.x() * cx2 + a.x() * cy2 + b.x() * ax2 + b.x() * ay2 + c.x() * bx2 + c.x() * by2 //
                         - a.x() * bx2 - a.x() * by2 - b.x() * cx2 - b.x() * cy2 - c.x() * ax2 - c.x() * ay2);

            QRectF br(o + QPointF(r, r), o - QPointF(r, r));
            QLineF oa(o, a);
            QLineF ob(o, b);

            //            QPainterPath pp;
            //            pp.moveTo(o);
            //            qDebug() << "angle 1" << oa.angle();
            //            qDebug() << "angle 2" << oa.angleTo(ob);
            //            pp.arcTo(br, oa.angle(), oa.angleTo(ob));
            //            scene->addPath(pp, QPen(QColor(0, 255, 255, 100), constantWidth), Qt::NoBrush);

            auto item = scene->addEllipse(QRectF(o + QPointF(r, r), o - QPointF(r, r)), QPen(QColor(0, 0, 0, 100), constantWidth), Qt::NoBrush);
            item->setStartAngle(ob.angle() * 16);
            item->setSpanAngle(ob.angleTo(oa) * 16);
        }
    } else {
        scene->addPolygon(poly, QPen(QColor(0, 0, 0, 100), constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
    }
}

void LWPOLYLINE::drawInsert(INSERT_ET* i) const
{
    //    qDebug(Q_FUNC_INFO);
    //QPen p(QColor(0, 0, 0, 100), constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen p(QColor(0, 255, 255, 100), 0.0);
    if (bulge != 0.0) {

        QLineF l1(poly.first(), poly.last());
        double d = l1.length() * 0.5;
        double h = d * bulge;
        double r = (h * h + d * d) / (h * 2);
        QLineF l2(l1.center(), poly.last());
        QLineF n(l2.normalVector());
        n.setLength(h);

        QPointF a(poly.first());
        QPointF b(poly.last());
        QPointF c(n.p2());

        {
            QPointF o;
            double ax2 = a.x() * a.x();
            double bx2 = b.x() * b.x();
            double cx2 = c.x() * c.x();

            double ay2 = a.y() * a.y();
            double by2 = b.y() * b.y();
            double cy2 = c.y() * c.y();
            double D = a.x() * b.y() + a.y() * c.x() - b.y() * c.x() - a.x() * c.y() - b.x() * a.y() + b.x() * c.y();

            o.rx() = +0.5 / D * ( //
                         +a.y() * cx2 + a.y() * cy2 + b.y() * ax2 + b.y() * ay2 + c.y() * bx2 + c.y() * by2 //
                         - a.y() * bx2 - a.y() * by2 - b.y() * cx2 - b.y() * cy2 - c.y() * ax2 - c.y() * ay2);
            o.ry() = -0.5 / D * ( //
                         +a.x() * cx2 + a.x() * cy2 + b.x() * ax2 + b.x() * ay2 + c.x() * bx2 + c.x() * by2 //
                         - a.x() * bx2 - a.x() * by2 - b.x() * cx2 - b.x() * cy2 - c.x() * ax2 - c.x() * ay2);

            QRectF br(o + QPointF(r, r), o - QPointF(r, r));
            QLineF oa(o, a);
            QLineF ob(o, b);

            //            QPainterPath pp;
            //            pp.moveTo(o);
            //            qDebug() << "angle 1" << oa.angle();
            //            qDebug() << "angle 2" << oa.angleTo(ob);
            //            pp.arcTo(br, oa.angle(), oa.angleTo(ob));
            //            scene->addPath(pp, QPen(QColor(0, 255, 255, 100), constantWidth), Qt::NoBrush);

            for (int r = 0; r < i->rowCount; ++r) {
                for (int c = 0; c < i->colCount; ++c) {
                    QPointF tr(r * i->rowSpacing, r * i->colSpacing);
                    auto item = scene->addEllipse(QRectF(o + QPointF(r, r), o - QPointF(r, r)), QPen(QColor(0, 255, 255, 100), constantWidth), Qt::NoBrush);
                    item->setStartAngle(ob.angle() * 16);
                    item->setSpanAngle(ob.angleTo(oa) * 16);
                    item->setPos(i->insPt + tr);
                    item->setScale(i->scaleX /*, i->scaleY*/);
                    item->setRotation(i->rotationAngle);
                }
            }
        }
    } else {
        for (int r = 0; r < i->rowCount; ++r) {
            for (int c = 0; c < i->colCount; ++c) {
                QPointF tr(r * i->rowSpacing, r * i->colSpacing);
                auto item = scene->addPolygon(poly, QPen(QColor(0, 255, 255, 100), constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
                item->setPos(i->insPt + tr);
                item->setScale(i->scaleX /*, i->scaleY*/);
                item->setRotation(i->rotationAngle);
            }
        }
    }
}

void LWPOLYLINE::parse(CodeData& code)
{
    do {
        data << code;
        switch (static_cast<VarType>(code.code)) {
        case SubclassMrker:
            break;
        case NumberOfVertices:
            numberOfVertices = code.getInteger();
            poly.resize(numberOfVertices);
            break;
        case PolylineFlag:
            polylineFlag = code.getInteger();
            break;
        case ConstantWidth:
            constantWidth = code.getDouble();
            break;
        case Elevation:
            elevation = code.getDouble();
            break;
        case Thickness:
            thickness = code.getDouble();
            break;
        case VertexCoordinatesX:
            poly[counter].rx() = code.getDouble();
            break;
        case VertexCoordinatesY:
            poly[counter++].ry() = code.getDouble();
            break;
        case VertexID:
            break;
        case StartWidth:
            startWidth = code.getDouble();
            break;
        case EndWidth:
            endWidth = code.getDouble();
            break;
        case Bulge:
            bulge = code.getDouble();
            break;
        case ExtrDirX:
            break;
        case ExtrDirY:
            break;
        case ExtrDirZ:
            break;
        }
        code = sp->nextCode();
    } while (code.code != 0);
    code = sp->prevCode();
}
