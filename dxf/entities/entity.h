#pragma once
#include <QObject>

#include <dxf/codedata.h>

#ifndef ENTITY_H
#define ENTITY_H
struct Entity {
    QVector<CodeData> data;
    Entity();
    virtual ~Entity() { }
    virtual void draw() const = 0;
    virtual void parse(CodeData& code) = 0;
    static int toType(const QString& key);
    enum Type {
        ACAD_PROXY_ENTITY,
        ARC,
        ATTDEF,
        ATTRIB,
        BODY,
        CIRCLE,
        DIMENSION,
        ELLIPSE,
        HATCH,
        HELIX,
        IMAGE,
        INSERT,
        LEADER,
        LIGHT,
        LINE,
        LWPOLYLINE,
        MESH,
        MLEADER,
        MLEADERSTYLE,
        MLINE,
        MTEXT,
        OLE2FRAME,
        OLEFRAME,
        POINT,
        POLYLINE,
        RAY,
        REGION,
        SECTION,
        SEQEND,
        SHAPE,
        SOLID,
        SPLINE,
        SUN,
        SURFACE,
        TABLE,
        TEXT,
        TOLERANCE,
        TRACE,
        UNDERLAY,
        VERTEX,
        VIEWPORT,
        WIPEOUT,
        XLINE,
        //3DFACE,
        //3DSOLID,
    };
    Q_ENUM(Type)
    Q_GADGET
};
#endif // ENTITY_H

#include "arc.h"
#include "attdef.h"
#include "attrib.h"
#include "body.h"
#include "circle.h"
#include "dimension.h"
#include "ellipse.h"
#include "hatch.h"
#include "helix.h"
#include "image.h"
#include "insert.h"
#include "leader.h"
#include "light.h"
#include "line.h"
#include "lwpolyline.h"
#include "mesh.h"
#include "mleader.h"
#include "mleaderstyle.h"
#include "mline.h"
#include "mtext.h"
#include "ole2frame.h"
#include "oleframe.h"
#include "point.h"
#include "polyline.h"
#include "ray.h"
#include "region.h"
#include "section.h"
#include "seqend.h"
#include "shape.h"
#include "solid.h"
#include "spline.h"
#include "sun.h"
#include "surface.h"
#include "table.h"
#include "text.h"
#include "tolerance.h"
#include "trace.h"
#include "underlay.h"
#include "vertex.h"
#include "viewport.h"
#include "wipeout.h"
#include "xline.h"
