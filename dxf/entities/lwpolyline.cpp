#include "lwpolyline.h"
#include <QGraphicsScene>
#include <QPolygonF>
#include <dxf/dxf.h>

extern QGraphicsScene* scene;

LWPOLYLINE::LWPOLYLINE()
{
}

void LWPOLYLINE::draw() const
{    qDebug(Q_FUNC_INFO);

    QPolygonF poly;
    QPointF pt;
    double width = 0;
    for (auto& d : data) {
        if (d.code == 10) {
            pt.rx() = std::get<double>(d._val);
        } else if (d.code == 20) {
            pt.ry() = std::get<double>(d._val);
            poly.append(pt);
        } else if (d.code == 11) {
            pt.rx() = std::get<double>(d._val);
        } else if (d.code == 21) {
            pt.ry() = std::get<double>(d._val);
            poly.append(pt);
        } else if (d.code == 40) {
            width = std::get<double>(d._val);
        }
    }
    scene->addPolygon(poly, QPen(Qt::black, constantWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
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
            break;
        case PolylineFlag:
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
            break;
        case VertexCoordinatesY:
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
