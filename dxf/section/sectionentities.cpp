#include "sectionentities.h"
#include "../dxf.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <dxf/entities/insert.h>
#include <dxf/entities/polyline.h>

extern QGraphicsScene* scene;

SectionENTITIES::SectionENTITIES(const QVector<CodeData>& data)
    : SectionParser(data)
{
}

SectionENTITIES::SectionENTITIES(CodeData& code)
    : SectionParser({ {}, {} })
{
    qDebug(Q_FUNC_INFO);
    dontSkip = false;
    while (code.rawVal != "ENDBLK") {
        // Прочитать другую пару код / значение
        if (dontSkip)
            code = DxfFile::ReadCodes();
        if (code.rawVal == "ENDBLK")
            break;
        if (iParse(code))
            continue;
        dontSkip = true;
    }
}

void SectionENTITIES::parse()
{
    qDebug(Q_FUNC_INFO);
    dontSkip = true;
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        if (dontSkip)
            code = DxfFile::ReadCodes();
        data << code;
        if (code.rawVal == "ENDSEC")
            break;
        if (iParse(code))
            continue;
        dontSkip = true;
    }

    for (auto e : entities) {
        e->draw();
    }

    QTimer::singleShot(100, [] {
        auto r = scene->itemsBoundingRect();
        r.moveTopLeft(r.topLeft() + QPointF { +1, +1 });
        r.moveBottomRight(r.bottomRight() + QPointF { -1, -1 });
        scene->setSceneRect(r);
        reinterpret_cast<QGraphicsView*>(scene->parent())->scale(100, 100);
        reinterpret_cast<QGraphicsView*>(scene->parent())->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    });
}

bool SectionENTITIES::iParse(CodeData& code)
{
    if (int k = Entity::toType(code.rawVal); k > -1)
        key = static_cast<Entity::Type>(k);
    switch (key) {
    case Entity::ACAD_PROXY_ENTITY:
        return false;
    case Entity::ARC:
        return false;
    case Entity::ATTDEF:
        return false;
    case Entity::ATTRIB:
        return false;
    case Entity::BODY:
        return false;
    case Entity::CIRCLE:
        return false;
    case Entity::DIMENSION:
        return false;
    case Entity::ELLIPSE:
        return false;
    case Entity::HATCH:
        return false;
    case Entity::HELIX:
        return false;
    case Entity::IMAGE:
        return false;
    case Entity::INSERT:
        entities.append(new INSERT);
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        dontSkip = false;
        return true;
    case Entity::LEADER:
        return false;
    case Entity::LIGHT:
        return false;
    case Entity::LINE:
        return false;
    case Entity::LWPOLYLINE:
        return false;
    case Entity::MESH:
        return false;
    case Entity::MLEADER:
        return false;
    case Entity::MLEADERSTYLE:
        return false;
    case Entity::MLINE:
        return false;
    case Entity::MTEXT:
        return false;
    case Entity::OLE2FRAME:
        return false;
    case Entity::OLEFRAME:
        return false;
    case Entity::POINT:
        return false;
    case Entity::POLYLINE: ////////////
        entities.append(new POLYLINE);
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        //            entities[key].last() << code;
        //            while (key == Entity::POLYLINE && code.rawVal != "SEQEND") {
        //                // Прочитать другую пару код / значение
        //                code = DxfFile::ReadCodes();
        //                data << code;
        //                entities[key].last() << code;
        //            }
        return false;
    case Entity::RAY:
        return false;
    case Entity::REGION:
        return false;
    case Entity::SECTION:
        return false;
    case Entity::SEQEND:
        return false;
    case Entity::SHAPE:
        return false;
    case Entity::SOLID:
        return false;
    case Entity::SPLINE:
        return false;
    case Entity::SUN:
        return false;
    case Entity::SURFACE:
        return false;
    case Entity::TABLE:
        return false;
    case Entity::TEXT:
        return false;
    case Entity::TOLERANCE:
        return false;
    case Entity::TRACE:
        return false;
    case Entity::UNDERLAY:
        return false;
    case Entity::VERTEX:
        return false;
    case Entity::VIEWPORT:
        return false;
    case Entity::WIPEOUT:
        return false;
    case Entity::XLINE:
        return false;
    }
}

//    for (auto [key, val] : entities) {
//        qDebug() << key << val.size();
//    }
//    {
//        for (auto& val : entities[Entity::INSERT]) {
//            // qDebug() << val << "\r\r";
//            //            QMap<int, double> values;
//            //            for (auto& data : val) {
//            //                if (data.type == CodeData::Double)
//            //                    values[data.code] = std::get<double>(data._val);
//            //                else if (data.type == CodeData::Integer)
//            //                    values[data.code] = std::get<qint64>(data._val);
//            //            }
//            //            scene->addLine({ { values[10], values[20] }, { values[11], values[21] } }, QPen(Qt::black, 0.0));
//        }
//    }
//    {
//        for (auto& val : entities[Entity::LINE]) {
//            QMap<int, double> values;
//            for (auto& data : val) {
//                if (data.type == CodeData::Double)
//                    values[data.code] = std::get<double>(data._val);
//                else if (data.type == CodeData::Integer)
//                    values[data.code] = std::get<qint64>(data._val);
//            }
//            scene->addLine({ { values[10], values[20] }, { values[11], values[21] } }, QPen(Qt::black, 0.0));
//        }
//    }
//    {
//        for (auto& val : entities[Entity::LWPOLYLINE]) {
//            QPolygonF poly;
//            int counter = 0;
//            for (auto& data : val) {
//                if (data.code == 90) {
//                    poly.resize(std::get<qint64>(data._val));
//                } else if (data.code == 10) {
//                    poly[counter].rx() = std::get<double>(data._val);
//                } else if (data.code == 20) {
//                    poly[counter].ry() = std::get<double>(data._val);
//                    ++counter;
//                }
//            }
//            scene->addPolygon(poly, QPen(Qt::red, 0.0), Qt::NoBrush);
//        }
//    }
//    {
//        for (auto& val : entities[Entity::SOLID]) {
//            QPolygonF poly;
//            QPointF pt;
//            for (auto& data : val) {
//                if (data.code == 10) {
//                    pt.rx() = std::get<double>(data._val);
//                } else if (data.code == 20) {
//                    pt.ry() = std::get<double>(data._val);
//                    poly.append(pt);
//                } else if (data.code == 11) {
//                    pt.rx() = std::get<double>(data._val);
//                } else if (data.code == 21) {
//                    pt.ry() = std::get<double>(data._val);
//                    poly.append(pt);
//                }
//            }
//            scene->addPolygon(poly, QPen(Qt::green, 0.0), Qt::NoBrush);
//        }
//    }
