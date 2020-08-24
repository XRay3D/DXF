#include "circle.h"
#include "insert.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <section/blocks.h>
#include <section/entities.h>

extern QGraphicsScene* scene;

CIRCLE::CIRCLE(SectionParser* sp)
    : Entity(sp)
{
}

void CIRCLE::draw(const INSERT_ET* const i) const
{
    if (i) {
        for (int r = 0; r < i->rowCount; ++r) {
            for (int c = 0; c < i->colCount; ++c) {
                QPointF tr(r * i->rowSpacing, r * i->colSpacing);
                QPointF r(radius, radius);
                auto item = scene->addEllipse(QRectF(centerPoint - r, centerPoint + r), QPen(i->color(), thickness /*, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin*/), Qt::NoBrush);
                item->setToolTip(layerName);
                i->transform(item, tr);
                i->attachToLayer(item);
            }
        }
    } else {
        QPointF r(radius, radius);
        attachToLayer(scene->addEllipse(QRectF(centerPoint - r, centerPoint + r),
            QPen(i->color(), thickness /*, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin*/), Qt::NoBrush));
    }
}

void CIRCLE::parse(CodeData& code)
{
    do {
        data << code;
        switch (static_cast<VarType>(code.code)) {
        case SubclassMarker:
            break;
        case Thickness:
            thickness = code.getDouble();
            break;
        case CenterPointX:
            centerPoint.rx() = code.getDouble();
            break;
        case CenterPointY:
            centerPoint.ry() = code.getDouble();
            break;
        case CenterPointZ:
            break;
        case Radius:
            radius = code.getDouble();
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
    } while (code.code != 0);
}
