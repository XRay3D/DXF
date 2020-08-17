#pragma once

#include "section.h"

///////////////////////////////////////
/// \brief The SectionENTITIES struct
///
struct SectionENTITIES final : Section {
    SectionENTITIES(const QVector<CodeData>& data);
    virtual ~SectionENTITIES() = default;
    // Section interface
    void parse() override;
    enum ent {
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
    std::map<QString, QVector<QVector<CodeData>>> entities;

    Q_GADGET
    Q_ENUM(ent)
};
