#include "line.h"
#include <QGraphicsItem>
#include <QGraphicsScene>

extern QGraphicsScene* scene;

LINE::LINE(SectionParser* sp)
    : Entity(sp)
{
}

void LINE::draw(const INSERT_ET* const i) const
{
    if (i) {
        for (int r = 0; r < i->rowCount; ++r) {
            for (int c = 0; c < i->colCount; ++c) {
                QPointF tr(r * i->rowSpacing, r * i->colSpacing);
                auto item = scene->addLine({ startPoint, endPoint }, QPen(i->color(), thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                item->setToolTip(layerName);
                i->transform(item, tr);
                i->attachToLayer(item);
            }
        }
    } else {
        attachToLayer(scene->addLine({ startPoint, endPoint }, QPen(color(), thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)));
    }
}

void LINE::parse(CodeData& code)
{
    do {
        data << code;
        switch (static_cast<VarType>(code.code())) {
        case SubclassMarker:
            break;
        case Thickness:
            thickness = code;
            break;
        case StartPointX:
            startPoint.rx() = code;
            break;
        case StartPointY:
            startPoint.ry() = code;
            break;
        case StartPointZ:
            break;
        case EndPointX:
            endPoint.rx() = code;
            break;
        case EndPointY:
            endPoint.ry() = code;
            break;
        case EndPointZ:
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
}
