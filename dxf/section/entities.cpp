#include "entities.h"
#include "../dxf.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <dxf/entities/entity.h>

extern QGraphicsScene* scene;

SectionENTITIES::SectionENTITIES(QMap<QString, Block*>& blocks, QVector<CodeData>&& data)
    : SectionParser(std::move(data))
    , sp(this)
    , blocks(blocks)
{
}

SectionENTITIES::SectionENTITIES(QMap<QString, Block*>& blocks, CodeData& code, SectionParser* sp)
    : SectionParser({ {}, {} })
    , sp(sp)
    , blocks(blocks)
{
    do {
        iParse(code);
    } while (code.rawVal != "ENDBLK");
}

void SectionENTITIES::parse()
{
    code = nextCode();
    code = nextCode();
    code = nextCode();
    while (code.rawVal != "ENDSEC") {
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
