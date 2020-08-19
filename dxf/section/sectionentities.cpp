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

void SectionENTITIES::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    Entity::Type key;
    bool dontSkip = true;
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        if (dontSkip)
            code = DxfFile::ReadCodes();

        data << code;
        if (code.rawVal == "ENDSEC") {
            break;
        } else if (int k = Entity::toType(code.rawVal); k > -1) {
            key = static_cast<Entity::Type>(k);
        }
        switch (key) {
        case Entity::ACAD_PROXY_ENTITY:
            break;
        case Entity::ARC:
            break;
        case Entity::ATTDEF:
            break;
        case Entity::ATTRIB:
            break;
        case Entity::BODY:
            break;
        case Entity::CIRCLE:
            break;
        case Entity::DIMENSION:
            break;
        case Entity::ELLIPSE:
            break;
        case Entity::HATCH:
            break;
        case Entity::HELIX:
            break;
        case Entity::IMAGE:
            break;
        case Entity::INSERT:
            entities.append(new INSERT);
            entities.last()->parse(code);
            entitiesMap[key] << entities.last();
            dontSkip = false;
            continue;
        case Entity::LEADER:
            break;
        case Entity::LIGHT:
            break;
        case Entity::LINE:
            break;
        case Entity::LWPOLYLINE:
            break;
        case Entity::MESH:
            break;
        case Entity::MLEADER:
            break;
        case Entity::MLEADERSTYLE:
            break;
        case Entity::MLINE:
            break;
        case Entity::MTEXT:
            break;
        case Entity::OLE2FRAME:
            break;
        case Entity::OLEFRAME:
            break;
        case Entity::POINT:
            break;
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
            break;
        case Entity::RAY:
            break;
        case Entity::REGION:
            break;
        case Entity::SECTION:
            break;
        case Entity::SEQEND:
            break;
        case Entity::SHAPE:
            break;
        case Entity::SOLID:
            break;
        case Entity::SPLINE:
            break;
        case Entity::SUN:
            break;
        case Entity::SURFACE:
            break;
        case Entity::TABLE:
            break;
        case Entity::TEXT:
            break;
        case Entity::TOLERANCE:
            break;
        case Entity::TRACE:
            break;
        case Entity::UNDERLAY:
            break;
        case Entity::VERTEX:
            break;
        case Entity::VIEWPORT:
            break;
        case Entity::WIPEOUT:
            break;
        case Entity::XLINE:
            break;
        }
        dontSkip = true;
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
    //    {
    //        for (auto& val : entities[Entity::POLYLINE]) {
    //            QPolygonF poly;
    //            QPointF pt;
    //            double width = 0;
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
    //                } else if (data.code == 40) {
    //                    width = std::get<double>(data._val);
    //                }
    //            }
    //            scene->addPolygon(poly, QPen(Qt::black, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
    //        }
    //    }

    for (auto e : entities) {
        e->draw();
    }
    {
        QVector<Entity::Type> keys;
        keys.reserve(entitiesMap.size());
        for (auto& [Key, Val] : entitiesMap)
            keys.push_back(Key);
        qDebug() << keys;
    }

    QTimer::singleShot(100, [] {
        auto r = scene->itemsBoundingRect();
        r.moveTopLeft(r.topLeft() + QPointF { +1, +1 });
        r.moveBottomRight(r.bottomRight() + QPointF { -1, -1 });
        scene->setSceneRect(r);
        reinterpret_cast<QGraphicsView*>(scene->parent())->scale(100, 100);
        reinterpret_cast<QGraphicsView*>(scene->parent())->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    });
    //    qDebug() << scene;
}
