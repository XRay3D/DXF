# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/block.h \
    $$PWD/codedata.h \
    $$PWD/dxf.h \
    $$PWD/dxfvalues.h \
    $$PWD/entities/arc.h \
    $$PWD/entities/attdef.h \
    $$PWD/entities/attrib.h \
    $$PWD/entities/body.h \
    $$PWD/entities/circle.h \
    $$PWD/entities/dimension.h \
    $$PWD/entities/ellipse.h \
    $$PWD/entities/entity.h \
    $$PWD/entities/hatch.h \
    $$PWD/entities/helix.h \
    $$PWD/entities/image.h \
    $$PWD/entities/insert.h \
    $$PWD/entities/leader.h \
    $$PWD/entities/light.h \
    $$PWD/entities/line.h \
    $$PWD/entities/lwpolyline.h \
    $$PWD/entities/mesh.h \
    $$PWD/entities/mleader.h \
    $$PWD/entities/mleaderstyle.h \
    $$PWD/entities/mline.h \
    $$PWD/entities/mtext.h \
    $$PWD/entities/ole2frame.h \
    $$PWD/entities/oleframe.h \
    $$PWD/entities/point.h \
    $$PWD/entities/polyline.h \
    $$PWD/entities/ray.h \
    $$PWD/entities/region.h \
    $$PWD/entities/section.h \
    $$PWD/entities/shape.h \
    $$PWD/entities/solid.h \
    $$PWD/entities/spline.h \
    $$PWD/entities/sun.h \
    $$PWD/entities/surface.h \
    $$PWD/entities/table.h \
    $$PWD/entities/text.h \
    $$PWD/entities/tolerance.h \
    $$PWD/entities/trace.h \
    $$PWD/entities/underlay.h \
    $$PWD/entities/vertex.h \
    $$PWD/entities/viewport.h \
    $$PWD/entities/wipeout.h \
    $$PWD/entities/xline.h \
    $$PWD/header.h \
    $$PWD/section/blocks.h \
    $$PWD/section/classes.h \
    $$PWD/section/entities.h \
    $$PWD/section/headerparser.h \
    $$PWD/section/objects.h \
    $$PWD/section/sectionparser.h \
    $$PWD/section/tables.h \
    $$PWD/section/thumbnailimage.h \
    $$PWD/tables/appid.h \
    $$PWD/tables/block_record.h \
    $$PWD/tables/dimstyle.h \
    $$PWD/tables/layer.h \
    $$PWD/tables/layermodel.h \
    $$PWD/tables/ltype.h \
    $$PWD/tables/style.h \
    $$PWD/tables/tableitem.h \
    $$PWD/tables/ucs.h \
    $$PWD/tables/view.h \
    $$PWD/tables/vport.h

SOURCES += \
    $$PWD/block.cpp \
    $$PWD/codedata.cpp \
    $$PWD/dxf.cpp \
    $$PWD/dxfvalues.cpp \
    $$PWD/entities/arc.cpp \
    $$PWD/entities/attdef.cpp \
    $$PWD/entities/attrib.cpp \
    $$PWD/entities/body.cpp \
    $$PWD/entities/circle.cpp \
    $$PWD/entities/dimension.cpp \
    $$PWD/entities/ellipse.cpp \
    $$PWD/entities/entity.cpp \
    $$PWD/entities/hatch.cpp \
    $$PWD/entities/helix.cpp \
    $$PWD/entities/image.cpp \
    $$PWD/entities/insert.cpp \
    $$PWD/entities/leader.cpp \
    $$PWD/entities/light.cpp \
    $$PWD/entities/line.cpp \
    $$PWD/entities/lwpolyline.cpp \
    $$PWD/entities/mesh.cpp \
    $$PWD/entities/mleader.cpp \
    $$PWD/entities/mleaderstyle.cpp \
    $$PWD/entities/mline.cpp \
    $$PWD/entities/mtext.cpp \
    $$PWD/entities/ole2frame.cpp \
    $$PWD/entities/oleframe.cpp \
    $$PWD/entities/point.cpp \
    $$PWD/entities/polyline.cpp \
    $$PWD/entities/ray.cpp \
    $$PWD/entities/region.cpp \
    $$PWD/entities/section.cpp \
    $$PWD/entities/shape.cpp \
    $$PWD/entities/solid.cpp \
    $$PWD/entities/spline.cpp \
    $$PWD/entities/sun.cpp \
    $$PWD/entities/surface.cpp \
    $$PWD/entities/table.cpp \
    $$PWD/entities/text.cpp \
    $$PWD/entities/tolerance.cpp \
    $$PWD/entities/trace.cpp \
    $$PWD/entities/underlay.cpp \
    $$PWD/entities/vertex.cpp \
    $$PWD/entities/viewport.cpp \
    $$PWD/entities/wipeout.cpp \
    $$PWD/entities/xline.cpp \
    $$PWD/header.cpp \
    $$PWD/section/blocks.cpp \
    $$PWD/section/classes.cpp \
    $$PWD/section/entities.cpp \
    $$PWD/section/headerparser.cpp \
    $$PWD/section/objects.cpp \
    $$PWD/section/sectionparser.cpp \
    $$PWD/section/tables.cpp \
    $$PWD/section/thumbnailimage.cpp \
    $$PWD/tables/appid.cpp \
    $$PWD/tables/block_record.cpp \
    $$PWD/tables/dimstyle.cpp \
    $$PWD/tables/layer.cpp \
    $$PWD/tables/layermodel.cpp \
    $$PWD/tables/ltype.cpp \
    $$PWD/tables/style.cpp \
    $$PWD/tables/tableitem.cpp \
    $$PWD/tables/ucs.cpp \
    $$PWD/tables/view.cpp \
    $$PWD/tables/vport.cpp
