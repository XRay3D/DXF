#include "entities.h"
#include "../dxf.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <dxf/entities/entity.h>

extern QGraphicsScene* scene;

SectionENTITIES::SectionENTITIES(QMap<QString, DxfBlock*>& blocks, QVector<CodeData>&& data)
    : SectionParser(std::move(data))
    , sp(this)
    , blocks(blocks)
{
}

SectionENTITIES::SectionENTITIES(QMap<QString, DxfBlock*>& blocks, CodeData& code, SectionParser* sp)
    : SectionParser({ {}, {} })
    , sp(sp)
    , blocks(blocks)
{
    do {
        iParse(code);
        code = sp->nextCode();
    } while (code.rawVal != "ENDBLK");
}

void SectionENTITIES::parse()
{
    qDebug(Q_FUNC_INFO);
    code = nextCode();
    code = nextCode();
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = nextCode();
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
    key = static_cast<Entity::Type>(Entity::toType(code.rawVal));
    switch (key) {
    case Entity::ACAD_PROXY_ENTITY:
        qDebug() << key << code.rawVal;
        break;
    case Entity::ARC:
        qDebug() << key << code.rawVal;
        break;
    case Entity::ATTDEF:
        qDebug() << key << code.rawVal;
        break;
    case Entity::ATTRIB:
        qDebug() << key << code.rawVal;
        break;
    case Entity::BODY:
        qDebug() << key << code.rawVal;
        break;
    case Entity::CIRCLE:
        entities.append(new CIRCLE(sp));
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::DIMENSION:
        qDebug() << key << code.rawVal;
        break;
    case Entity::ELLIPSE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::HATCH:
        entities.append(new HATCH(sp));
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::HELIX:
        qDebug() << key << code.rawVal;
        break;
    case Entity::IMAGE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::INSERT:
        entities.append(new INSERT_ET(blocks, sp));
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::LEADER:
        qDebug() << key << code.rawVal;
        break;
    case Entity::LIGHT:
        qDebug() << key << code.rawVal;
        break;
    case Entity::LINE:
        entities.append(new LINE(sp));
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::LWPOLYLINE:
        entities.append(new LWPOLYLINE(sp));
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::MESH:
        qDebug() << key << code.rawVal;
        break;
    case Entity::MLEADER:
        qDebug() << key << code.rawVal;
        break;
    case Entity::MLEADERSTYLE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::MLINE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::MTEXT:
        qDebug() << key << code.rawVal;
        break;
    case Entity::OLE2FRAME:
        qDebug() << key << code.rawVal;
        break;
    case Entity::OLEFRAME:
        qDebug() << key << code.rawVal;
        break;
    case Entity::POINT:
        qDebug() << key << code.rawVal;
        break;
    case Entity::POLYLINE: ////////////
        entities.append(new POLYLINE(sp));
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        //            entities[key].last() << code;
        //            while (key == Entity::POLYLINE && code.rawVal != "SEQEND") {
        //                // Прочитать другую пару код / значение
        //                code = nextCode();
        //                data << code;
        //                entities[key].last() << code;
        //            }
        return;
    case Entity::RAY:
        qDebug() << key << code.rawVal;
        break;
    case Entity::REGION:
        qDebug() << key << code.rawVal;
        break;
    case Entity::SECTION:
        qDebug() << key << code.rawVal;
        break;
    case Entity::SEQEND:
        qDebug() << key << code.rawVal;
        break;
    case Entity::SHAPE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::SOLID:
        entities.append(new SOLID(sp));
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::SPLINE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::SUN:
        qDebug() << key << code.rawVal;
        break;
    case Entity::SURFACE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::TABLE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::TEXT:
        entities.append(new TEXT(sp));
        entities.last()->parse(code);
        entitiesMap[key] << entities.last();
        return;
    case Entity::TOLERANCE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::TRACE:
        qDebug() << key << code.rawVal;
        break;
    case Entity::UNDERLAY:
        qDebug() << key << code.rawVal;
        break;
    case Entity::VERTEX:
        qDebug() << key << code.rawVal;
        break;
    case Entity::VIEWPORT:
        qDebug() << key << code.rawVal;
        break;
    case Entity::WIPEOUT:
        qDebug() << key << code.rawVal;
        break;
    case Entity::XLINE:
        qDebug() << key << code.rawVal;
        break;
    default:
        break;
    }
    qDebug() << key << code;
    exit(-1000);
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
//            //            scene->addLine({ { values[10], values[20] }, { values[11], values[21] } }, QPen(QColor(0, 0, 0, 100), 0.0));
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
//            scene->addLine({ { values[10], values[20] }, { values[11], values[21] } }, QPen(QColor(0, 0, 0, 100), 0.0));
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
//            scene->addPolygon(poly, QPen(QColor(0, 255, 255, 100), 0.0), Qt::NoBrush);
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
