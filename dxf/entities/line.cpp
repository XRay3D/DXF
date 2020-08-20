#include "line.h"
#include <QGraphicsScene>

extern QGraphicsScene* scene;

LINE::LINE(SectionParser* sp)
    : Entity(sp)
{
}

void LINE::draw() const
{
    scene->addLine({ startPoint, endPoint }, QPen(QColor(0, 0, 0, 100), thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void LINE::parse(CodeData& code)
{
    do {
        data << code;
        switch (static_cast<VarType>(code.code)) {
        case SubclassMarker:
            break;
        case Thickness:
            thickness = code.getDouble();
            break;
        case StartPointX:
            startPoint.rx() = code.getDouble();
            break;
        case StartPointY:
            startPoint.ry() = code.getDouble();
            break;
        case StartPointZ:
            break;
        case EndPointX:
            endPoint.rx() = code.getDouble();
            break;
        case EndPointY:
            endPoint.ry() = code.getDouble();
            break;
        case EndPointZ:
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
