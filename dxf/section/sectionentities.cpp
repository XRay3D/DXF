#include "sectionentities.h"
#include "../dxf.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <dxf/entities/entity.h>

extern QGraphicsScene* scene;

SectionENTITIES::SectionENTITIES(const QVector<CodeData>& data)
    : SectionParser(data)
{
}

SectionENTITIES::SectionENTITIES(CodeData& code)
    : SectionParser({ {}, {} })
{
    qDebug(Q_FUNC_INFO);
    while (code.rawVal != "ENDBLK") {
        // Прочитать другую пару код / значение
        //        code = DxfFile::ReadCodes();
        //        if (code.rawVal == "ENDBLK" || code.rawVal == "BLOCK")
        //            break;
        iParse(code);
        if (code.rawVal == "ENDBLK" || code.rawVal == "BLOCK")
            break;
    }
}

void SectionENTITIES::parse()
{
    qDebug(Q_FUNC_INFO);
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = DxfFile::ReadCodes();
        data << code;
        if (code.rawVal == "ENDSEC")
            break;
        iParse(code);
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

void SectionENTITIES::iParse(CodeData& code)
{

    //    Entity::CIRCLE
    //    Entity::HATCH
    //    Entity::INSERT
    //    Entity::LINE
    //    Entity::LWPOLYLINE
    //    Entity::SOLID
    //    Entity::TEXT

    key = static_cast<Entity::Type>(Entity::toType(code.rawVal));
    switch (key) {
    case Entity::ACAD_PROXY_ENTITY:
        qDebug() << key << code.rawVal;
        return;
    case Entity::ARC:
        qDebug() << key << code.rawVal;
        return;
    case Entity::ATTDEF:
        qDebug() << key << code.rawVal;
        return;
    case Entity::ATTRIB:
        qDebug() << key << code.rawVal;
        return;
    case Entity::BODY:
        qDebug() << key << code.rawVal;
        return;
    case Entity::CIRCLE:
        entities.append(new CIRCLE);
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::DIMENSION:
        qDebug() << key << code.rawVal;
        return;
    case Entity::ELLIPSE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::HATCH:
        entities.append(new HATCH);
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::HELIX:
        qDebug() << key << code.rawVal;
        return;
    case Entity::IMAGE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::INSERT:
        entities.append(new INSERT);
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::LEADER:
        qDebug() << key << code.rawVal;
        return;
    case Entity::LIGHT:
        qDebug() << key << code.rawVal;
        return;
    case Entity::LINE:
        entities.append(new LINE);
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::LWPOLYLINE:
        entities.append(new LWPOLYLINE);
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::MESH:
        qDebug() << key << code.rawVal;
        return;
    case Entity::MLEADER:
        qDebug() << key << code.rawVal;
        return;
    case Entity::MLEADERSTYLE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::MLINE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::MTEXT:
        qDebug() << key << code.rawVal;
        return;
    case Entity::OLE2FRAME:
        qDebug() << key << code.rawVal;
        return;
    case Entity::OLEFRAME:
        qDebug() << key << code.rawVal;
        return;
    case Entity::POINT:
        qDebug() << key << code.rawVal;
        return;
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
        return;
    case Entity::RAY:
        qDebug() << key << code.rawVal;
        return;
    case Entity::REGION:
        qDebug() << key << code.rawVal;
        return;
    case Entity::SECTION:
        qDebug() << key << code.rawVal;
        return;
    case Entity::SEQEND:
        qDebug() << key << code.rawVal;
        return;
    case Entity::SHAPE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::SOLID:
        entities.append(new SOLID);
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::SPLINE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::SUN:
        qDebug() << key << code.rawVal;
        return;
    case Entity::SURFACE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::TABLE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::TEXT:
        entities.append(new TEXT);
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::TOLERANCE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::TRACE:
        qDebug() << key << code.rawVal;
        return;
    case Entity::UNDERLAY:
        qDebug() << key << code.rawVal;
        return;
    case Entity::VERTEX:
        qDebug() << key << code.rawVal;
        return;
    case Entity::VIEWPORT:
        qDebug() << key << code.rawVal;
        return;
    case Entity::WIPEOUT:
        qDebug() << key << code.rawVal;
        return;
    case Entity::XLINE:
        qDebug() << key << code.rawVal;
        return;
    default:
        qDebug() << key << code.rawVal;
        exit(-1000);
    }
    qDebug() << key << code.rawVal;
    return;
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
