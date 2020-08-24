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
    qDebug() << entitiesMap.keys();
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

    qDebug() << entitiesMap.keys();

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
        exit(-1000);
        break;
    case Entity::ARC:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::ATTDEF:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::ATTRIB:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::BODY:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::CIRCLE:
        entities.append(new CIRCLE(sp));
        break;
    case Entity::DIMENSION:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::ELLIPSE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::HATCH:
        entities.append(new HATCH(sp));
        break;
    case Entity::HELIX:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::IMAGE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::INSERT:
        entities.append(new INSERT_ET(blocks, sp));
        break;
    case Entity::LEADER:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::LIGHT:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::LINE:
        entities.append(new LINE(sp));
        break;
    case Entity::LWPOLYLINE:
        entities.append(new LWPOLYLINE(sp));
        break;
    case Entity::MESH:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::MLEADER:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::MLEADERSTYLE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::MLINE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::MTEXT:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::OLE2FRAME:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::OLEFRAME:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::POINT:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::POLYLINE: ////////////
        entities.append(new POLYLINE(sp));
        break;
    case Entity::RAY:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::REGION:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::SECTION:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::SEQEND:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::SHAPE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::SOLID:
        entities.append(new SOLID(sp));
        break;
    case Entity::SPLINE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::SUN:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::SURFACE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::TABLE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::TEXT:
        entities.append(new TEXT(sp));
        break;
    case Entity::TOLERANCE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::TRACE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::UNDERLAY:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::VERTEX:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::VIEWPORT:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::WIPEOUT:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    case Entity::XLINE:
        qDebug() << key << code.rawVal;
        exit(-1000);
        break;
    default:
        break;
    }

    entities.last()->parse(code);
    entitiesMap[key] << entities.last();
}
