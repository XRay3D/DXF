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
    $$PWD/dl_attributes.h \
    $$PWD/dl_codes.h \
    $$PWD/dl_creationadapter.h \
    $$PWD/dl_creationinterface.h \
    $$PWD/dl_dxf.h \
    $$PWD/dl_entities.h \
    $$PWD/dl_exception.h \
    $$PWD/dl_extrusion.h \
    $$PWD/dl_global.h \
    $$PWD/dl_writer.h \
    $$PWD/dl_writer_ascii.h


SOURCES += \
    $$PWD/dl_dxf.cpp \
    $$PWD/dl_writer_ascii.cpp \

