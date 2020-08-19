#include "lwpolyline.h"
#include <QGraphicsScene>
#include <QPolygonF>
#include <dxf/dxf.h>

extern QGraphicsScene* scene;

LWPOLYLINE::LWPOLYLINE()
{
}

void LWPOLYLINE::draw() const
{
    qDebug(Q_FUNC_INFO);
    if (bulge != 0.0) { // решение в лоб
        QLineF l(poly.first(), poly.last());
        QRectF r;
        r.setLeft(l.p1().x());
        r.setRight(l.p2().x());
        r.setTop(l.p1().y() + l.length() / 2);
        r.setBottom(l.p2().y() - l.length() / 2);
        scene->addEllipse(r, QPen(Qt::black, constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
    } else
        scene->addPolygon(poly, QPen(Qt::red, constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
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
        code = DxfFile::ReadCodes();
    } while (code.code != 0);
    code = DxfFile::ReadCodes(true);
}
