#pragma once
#include <QObject>

#include <dxf/codedata.h>

struct Entity {
    QVector<CodeData> data;
    Entity();
    ~Entity() {}
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
