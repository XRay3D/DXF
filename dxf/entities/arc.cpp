#include "arc.h"

#include "insert.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <section/blocks.h>
#include <section/entities.h>

#include <QGraphicsItem>
#include <QPainter>

class ArcItem2 : public QGraphicsItem {
    const ARC* arc;
    QColor color;
    QPainterPath path;

public:
    ArcItem2(const ARC* arc, const QColor& color)
        : arc(arc)
        , color(color)
    {
        double aspan = arc->endAngle - arc->startAngle;

        if (const bool ccw = arc->endAngle > arc->startAngle;
            arc->endAngle >= 0 && arc->startAngle >= 0) {
            if (!ccw)
                aspan += 360;
        } else {
            if (aspan < -180 || (qFuzzyCompare(aspan, -180) && !ccw))
                aspan += 360;
            else if (aspan > 180 || (qFuzzyCompare(aspan, 180) && ccw))
                aspan -= 360;
        }

        setToolTip(QString("B%1 E%2 S%3").arg(arc->startAngle).arg(arc->endAngle).arg(aspan));

        path.moveTo(QLineF::fromPolar(arc->radius, -arc->startAngle).translated(arc->centerPoint).p2());
        QPointF rad(arc->radius, arc->radius);
        path.arcTo(QRectF(arc->centerPoint - rad, arc->centerPoint + rad), -arc->startAngle, -aspan);
    }

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override { return path.boundingRect(); }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) override
    {
        painter->setPen(QPen(color, arc->thickness));
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(path);
    }
};

extern QGraphicsScene* scene;

ARC::ARC(SectionParser* sp)
    : Entity(sp)
{
}

void ARC::draw(const INSERT_ET* const i) const
{
    if (i) {
        for (int r = 0; r < i->rowCount; ++r) {
            for (int c = 0; c < i->colCount; ++c) {
                QPointF tr(r * i->rowSpacing, r * i->colSpacing);
                QPointF rad(radius, radius);
                auto item = new ArcItem2(this, i->color());
                scene->addItem(item);
                //                item->setToolTip(layerName);
                i->transform(item, tr);
                i->attachToLayer(item);
            }
        }
    } else {
        auto item = new ArcItem2(this, color());
        scene->addItem(item);
        attachToLayer(item);
    }
}

void ARC::parse(CodeData& code)
{
    do {
        data << code;
        switch (static_cast<VarType>(code.code())) {
        case SubclassMarker:
            break;
        case Thickness:
            thickness = code;
            break;
        case CenterPointX:
            centerPoint.rx() = code;
            break;
        case CenterPointY:
            centerPoint.ry() = code;
            break;
        case CenterPointZ:
            break;
        case Radius:
            radius = code;
            break;
        case StartAngle:
            startAngle = code;
            break;
        case EndAngle:
            endAngle = code;
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
    qDebug() << QString("\n%1 %2").arg(startAngle, 6, 'f', 6).arg(endAngle, 6, 'f', 6).toLocal8Bit().data();
}
