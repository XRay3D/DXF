#include "solid.h"
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QPolygonF>
#include <dxf/dxf.h>

extern QGraphicsScene* scene;

SOLID::SOLID(SectionParser* sp)
    : Entity(sp)
{
}

void SOLID::draw() const
{
    QPolygonF poly;
    if (corners == 15) { //all
        poly.reserve(5);
        poly << firstCorner;
        poly << secondCorner;
        poly << fourthCorner;
        poly << thirdCorner;
        //        poly << firstCorner;
    }
    attachToLayer(scene->addPolygon(poly, QPen(color(), thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), color()));
}

void SOLID::drawInsert(INSERT_ET* i) const
{
    QPolygonF poly;
    if (corners == 15) { //all
        poly.reserve(5);
        poly << firstCorner;
        poly << secondCorner;
        poly << fourthCorner;
        poly << thirdCorner;
        //        poly << firstCorner;
    }
    for (int r = 0; r < i->rowCount; ++r) {
        for (int c = 0; c < i->colCount; ++c) {
            QPointF tr(r * i->rowSpacing, r * i->colSpacing);
            auto item = scene->addPolygon(poly, QPen(i->color(), thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), i->color());
            item->setPos(i->insPt + tr);
            item->setScale(i->scaleX /*, i->scaleY*/);
            item->setRotation(i->rotationAngle);
            i->attachToLayer(item);
        }
    }
}

void SOLID::parse(CodeData& code)
{
    do {
        data << code;
        switch (static_cast<VarType>(code.code)) {
        case SubclassMarker:
            break;
        case Thickness:
            thickness = code.getDouble();
            break;
        case FirstCornerX:
            firstCorner.rx() = code.getDouble();
            corners |= FirstCorner;
            break;
        case FirstCornerY:
            firstCorner.ry() = code.getDouble();
            break;
        case FirstCornerZ:
            break;
        case SecondCornerX:
            secondCorner.rx() = code.getDouble();
            corners |= SecondCorner;
            break;
        case SecondCornerY:
            secondCorner.ry() = code.getDouble();
            break;
        case SecondCornerZ:
            break;
        case ThirdCornerX:
            thirdCorner.rx() = code.getDouble();
            corners |= ThirdCorner;
            break;
        case ThirdCornerY:
            thirdCorner.ry() = code.getDouble();
            break;
        case ThirdCornerZ:
            break;
        case FourthCornerX:
            fourthCorner.rx() = code.getDouble();
            corners |= FourthCorner;
            break;
        case FourthCornerY:
            fourthCorner.ry() = code.getDouble();
            break;
        case FourthCornerZ:
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
    code = sp->prevCode();
}
