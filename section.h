#pragma once

#include "codedata.h"
#include <QDebug>
#include <QObject>
#include <QVector>

struct Entities {
    Entities() {}
    enum ent {
        //        3DFACE,
        //        3DSOLID,
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
        MLINE,
        MLEADERSTYLE,
        MLEADER,
        MTEXT,
        OLEFRAME,
        OLE2FRAME,
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
    };
    Q_ENUM(ent)
    Q_GADGET
};

struct Section {

    friend QDebug operator<<(QDebug debug, const Section& c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "\rSEC(" << c.type << ')';
        return debug;
    }

    enum sec {
        Null,
        HEADER,
        CLASSES,
        TABLES,
        BLOCKS,
        ENTITIES,
        OBJECTS,
        THUMBNAILIMAGE,
    };
    const sec type;
    QVector<CodeData> data;
    static int key(const QString& key);
    Section(const QVector<CodeData>& data);
    virtual ~Section() = default;
    virtual void parse() = 0;

    Q_GADGET
    Q_ENUM(sec)
};

struct SectionHEADER : Section {
    SectionHEADER(const QVector<CodeData>& data)
        : Section(data)
    {
    }
    virtual ~SectionHEADER() = default;
    // Section interface
    void parse() override;
    QMap<QString, QMap<int, QVariant>> hData;
};

struct SectionCLASSES : Section {
    SectionCLASSES(const QVector<CodeData>& data)
        : Section(data)
    {
    }
    virtual ~SectionCLASSES() = default;
    // Section interface
    void parse() override {}
};
struct SectionTABLES : Section {
    SectionTABLES(const QVector<CodeData>& data)
        : Section(data)
    {
    }
    virtual ~SectionTABLES() = default;
    // Section interface
    void parse() override;
};
struct SectionBLOCKS : Section {
    SectionBLOCKS(const QVector<CodeData>& data)
        : Section(data)
    {
    }
    virtual ~SectionBLOCKS() = default;
    // Section interface
    void parse() override {}
};
struct SectionENTITIES : Section {
    SectionENTITIES(const QVector<CodeData>& data)
        : Section(data)
    {
    }
    virtual ~SectionENTITIES() = default;
    // Section interface
    void parse() override {}
};
struct SectionOBJECTS : Section {
    SectionOBJECTS(const QVector<CodeData>& data)
        : Section(data)
    {
    }
    virtual ~SectionOBJECTS() = default;
    // Section interface
    void parse() override {}
};
struct SectionTHUMBNAILIMAGE : Section {
    SectionTHUMBNAILIMAGE(const QVector<CodeData>& data)
        : Section(data)
    {
    }
    virtual ~SectionTHUMBNAILIMAGE() = default;
    // Section interface
    void parse() override {}
};
