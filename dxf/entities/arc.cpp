#include "arc.h"

#include "insert.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <section/blocks.h>
#include <section/entities.h>

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
                QPainterPath path;
                double aspan = endAngle - startAngle;
                if (aspan < -180 || (qFuzzyCompare(aspan, -180) && !(endAngle > startAngle)))
                    aspan += 360;
                else if (aspan > 180 || (qFuzzyCompare(aspan, 180) && (endAngle > startAngle)))
                    aspan -= 360;
                path.moveTo(QLineF::fromPolar(radius, -startAngle).translated(centerPoint).p2());
                path.arcTo(QRectF(centerPoint - rad, centerPoint + rad), -startAngle, -aspan);
                auto item = scene->addPath(path, QPen(i->color(), thickness /*, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin*/), Qt::NoBrush);
                item->setToolTip(layerName);
                i->transform(item, tr);
                i->attachToLayer(item);
            }
        }
    } else {
        QPointF rad(radius, radius);
        QPainterPath path;
        double aspan = endAngle - startAngle;
        if (aspan < -180 || (qFuzzyCompare(aspan, -180) && !(endAngle > startAngle)))
            aspan += 360;
        else if (aspan > 180 || (qFuzzyCompare(aspan, 180) && (endAngle > startAngle)))
            aspan -= 360;
        path.moveTo(QLineF::fromPolar(radius, -startAngle).translated(centerPoint).p2());
        path.arcTo(QRectF(centerPoint - rad, centerPoint + rad), -startAngle, -aspan);
        attachToLayer(scene->addPath(path, QPen(i->color(), thickness /*, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin*/), Qt::NoBrush));
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
