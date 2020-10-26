#include "lwpolyline.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPainterPath>
#include <QPolygonF>
#include <QtMath>

extern QGraphicsScene* scene;

class ArcItem final : public QGraphicsItem {
    QPainterPath path;
    QPainterPath path1;
    const LWPOLYLINE* lwpl;
    QColor color;
    double aAngle;
    double bAngle;
    double radius;
    QPointF o;

    qreal angle(QPointF pt1, QPointF pt2) const
    {
        const qreal dx = pt2.x() - pt1.x();
        const qreal dy = pt2.y() - pt1.y();
        const qreal theta = qRadiansToDegrees(qAtan2(dy, -dx));
        const qreal theta_normalized = theta < 0 ? theta + 360 : theta;
        if (qFuzzyCompare(theta_normalized, qreal(360)))
            return qreal(0);
        else
            return theta_normalized;
    }

    void addSeg(LWPOLYLINE::Segment a, LWPOLYLINE::Segment b)
    {
        if (path.isEmpty())
            path.moveTo(a);

        if (qFuzzyIsNull(a.bulge)) {
            path.lineTo(b);
            return;
        }
        return;

        const QLineF l1(a, b);
        const double lenght = l1.length() * 0.5;
        const double height = lenght * a.bulge;
        radius = (height * height + lenght * lenght) / (height * 2);
        QLineF l2(l1.center(), b);
        l2 = l2.normalVector();
        l2.setLength(height);

        QPointF c(l2.p2());

        {
            double ax2 = a.x() * a.x();
            double bx2 = b.x() * b.x();
            double cx2 = c.x() * c.x();

            double ay2 = a.y() * a.y();
            double by2 = b.y() * b.y();
            double cy2 = c.y() * c.y();
            double D = a.x() * b.y() + a.y() * c.x() - b.y() * c.x() - a.x() * c.y() - b.x() * a.y() + b.x() * c.y();

            o.rx() = +0.5 / D * ( //
                         a.y() * cx2 + a.y() * cy2 + b.y() * ax2 + b.y() * ay2 + c.y() * bx2 + c.y() * by2 - //
                         a.y() * bx2 - a.y() * by2 - b.y() * cx2 - b.y() * cy2 - c.y() * ax2 - c.y() * ay2);
            o.ry() = -0.5 / D * ( //
                         a.x() * cx2 + a.x() * cy2 + b.x() * ax2 + b.x() * ay2 + c.x() * bx2 + c.x() * by2 - //
                         a.x() * bx2 - a.x() * by2 - b.x() * cx2 - b.x() * cy2 - c.x() * ax2 - c.x() * ay2);
        }

        //path.addEllipse(QRectF(o - QPointF(0.1, 0.1), o + QPointF(0.1, 0.1))); ///////dbg

        path1.moveTo(a);
        path1.lineTo(b);
        path1.lineTo(c);
        path1.lineTo(a);

        path1.addEllipse(QRectF(c - QPointF(0.1, 0.1), c + QPointF(0.1, 0.1))); ///////dbg

        QRectF br(o + QPointF(radius, radius), o - QPointF(radius, radius));

        aAngle = angle(o, a);
        bAngle = angle(o, b);

        if (lwpl->polylineFlag == LWPOLYLINE::Closed) {
            double angle = bAngle - aAngle;
            if (angle < 0)
                angle += 360;
            if (aAngle < 0 || bAngle < 0)
                return;
            //path.moveTo(b);
            path.arcTo(br, aAngle, angle);
            path.arcTo(br, bAngle, angle);
        } else {
            qDebug() << "\nA" << aAngle
                     << "\nB" << bAngle;
            do {
                double angle = bAngle - aAngle;
                qDebug() << "A1" << angle;
                if (angle < 0)
                    angle += 360;
                if (aAngle < 0 || bAngle < 0)
                    break;
                //path.moveTo(b);
                path.arcTo(br, bAngle, angle - 360);
                qDebug() << "A1" << (angle - 360);
            } while (0);
        }
    }

public:
    ArcItem(const LWPOLYLINE* lwpl, const QColor& color)
        : lwpl(lwpl)
        , color(color)
    {
        for (int i = 0; i < lwpl->poly.size() - 1; ++i) {
            addSeg(lwpl->poly[i], lwpl->poly[i + 1]);
        }
    }

    ~ArcItem() = default;

    // QGraphicsItem interface
    QRectF boundingRect() const override { return path.boundingRect(); }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) override
    {
        painter->setPen(QPen(color, lwpl->constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(path);

        painter->setPen(QPen(Qt::blue /*color*/, 0.0 /*lwpl->constantWidth*/, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(path1);

        return;
        auto p = path.toSubpathPolygons(matrix());
        //        p.removeFirst();
        //        p.removeLast();
        if (p.size())
            painter->drawPolyline(p.first());
        //painter->drawArc(QRectF(o + QPointF(rad, rad), o - QPointF(rad, rad)), aAngle * 16, bAngle * 16);
    }
};

LWPOLYLINE::LWPOLYLINE(SectionParser* sp)
    : Entity(sp)
{
}

void LWPOLYLINE::draw(const INSERT_ET* const i) const
{
    if (i) {
        //        if (bulge != 0.0) {
        for (int r = 0; r < i->rowCount; ++r) {
            for (int c = 0; c < i->colCount; ++c) {
                QPointF tr(r * i->rowSpacing, r * i->colSpacing);
                auto item = new ArcItem(this, i->color());
                item->setPos(i->insPt + tr);
                item->setScale(i->scaleX /*, i->scaleY*/);
                item->setRotation(i->rotationAngle);
                scene->addItem(item);
                i->attachToLayer(item);
            }
        }
        //        } else {
        //        for (int r = 0; r < i->rowCount; ++r) {
        //            for (int c = 0; c < i->colCount; ++c) {
        //                QPointF tr(r * i->rowSpacing, r * i->colSpacing);
        //                auto item = scene->addPolygon(poly, QPen(i->color(), constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
        //                item->setToolTip(layerName);
        //                i->transform(item, tr);
        //                i->attachToLayer(item);
        //            }
        //        }
        //        }
    } else {
        //        if (bulge != 0.0) {
        //            //        return;
        auto item = new ArcItem(this, color());
        scene->addItem(item);
        attachToLayer(item);
        //        } else {
        //            attachToLayer(scene->addPolygon(poly, QPen(color(), constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush));
        //        }
    }
}

void LWPOLYLINE::parse(CodeData& code)
{
    Segment pt;
    do {
        data << code;
        switch (static_cast<VarType>(code.code())) {
        case SubclassMrker:
            break;
        case NumberOfVertices:
            numberOfVertices = code;
            break;
        case PolylineFlag:
            polylineFlag = code;
            break;
        case ConstantWidth:
            constantWidth = code;
            break;
        case Elevation:
            elevation = code;
            break;
        case Thickness:
            thickness = code;
            break;
        case VertexCoordinatesX:
            pt.rx() = code;
            break;
        case VertexCoordinatesY:
            pt.ry() = code;
            poly << pt;
            break;
        case VertexID:
            break;
        case StartWidth:
            startWidth = code;
            break;
        case EndWidth:
            endWidth = code;
            break;
        case Bulge: // betven points
            poly.last().bulge = code;
            break;
        case ExtrDirX:
            break;
        case ExtrDirY:
            break;
        case ExtrDirZ:
            break;
        default:
            parseEntity(code);
        }
        code = sp->nextCode();
    } while (code.code() != 0);
    qDebug() << poly.size();
}
