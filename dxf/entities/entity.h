#pragma once
#include <QObject>

#include <dxf/codedata.h>
#include <dxf/section/sectionparser.h>

struct INSERT_ET;
class QGraphicsItem;
#ifndef ENTITY_H
#define ENTITY_H

struct Entity {
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

    QVector<CodeData> data;
    SectionParser* sp = nullptr;
    Entity(SectionParser* sp);
    virtual ~Entity() { }
    virtual void draw(const INSERT_ET* const i = nullptr) const = 0;
    virtual void parse(CodeData& code) = 0;
    static Type TypeVal(const QString& key);
    static QString TypeName(int key);
    void parseEntity(CodeData& code);
    QColor color() const;
    void attachToLayer(QGraphicsItem* item) const;

    virtual Type type() const = 0;

    QString layerName;
    QString handle;

    enum VarType {
        EntityName = -1, //    Приложение: имя объекта (изменяется при каждом открытии чертежа)
        //    не пропускается
        EntityType = 0, //    Тип объекта
        //    не пропускается
        Handle = 5, //    Дескриптор
        //    не пропускается

        //        E102 = 102,
        //        //    Начало определенной в приложении группы
        //        //    "{имя_приложения" (необязательно)
        //        //    без значения по умолчанию
        //        //    коды, определенные в приложении
        //        //    Коды и значения в группах с кодом 102 определяются в приложении (необязательно)
        //        //    без значения по умолчанию
        //        E102 = 102,
        //        //    Конец группы, "}" (необязательно)
        //        //    без значения по умолчанию
        //        E102 = 102,
        //        //    "{ACAD_REACTORS" обозначает начало группы постоянных реакторов AutoCAD. Эта группа присутствует, только если постоянные реакторы были присоединены к данному объекту (необязательно)
        //        //    без значения по умолчанию

        SoftPointerID = 330, //    Идентификатор/дескриптор символьного указателя на словарь владельца (необязательно)
        //    без значения по умолчанию

        //        E102 = 102,        //    Конец группы, "}" (необязательно)
        //        //    без значения по умолчанию
        //        E102 = 102,        //    "{ACAD_XDICTIONARY" обозначает начало группы словаря расширения. Эта группа присутствует, только если словарь расширения был прикреплен к объекту (необязательно)
        //        //    без значения по умолчанию

        HardOwnerID = 360, //    Идентификатор/дескриптор жесткого указателя на словарь владельца (необязательно)
        //    без значения по умолчанию
        //        E102 = 102,
        //        //    Конец группы, "}" (необязательно)
        //    без значения по умолчанию
        //        E330 = 330,        //    Идентификатор/дескриптор символьного указателя на объект BLOCK_RECORD владельца
        //        //    не пропускается

        SubclassMarker = 100, //    Маркер подкласса (AcDbEntity)
        //    не пропускается
        E67 = 67, //    Отсутствие значения или ноль указывают на наличие объекта в пространстве модели. 1 указывает на наличие объекта в пространстве листа (необязательно).
        //E0 = 0,
        E410 = 410,
        //    Приложение: имя вкладки листа
        //    не пропускается
        LayerName = 8, //    Имя слоя
        //    не пропускается
        LineType = 6, //    Имя типа линий (присутствует, если значение — не ПОСЛОЮ). Специальное имя ПОБЛОКУ указывает на плавающий тип линий (необязательно)
        //    ПОСЛОЮ
        E347 = 347, //    Идентификатор/дескриптор жесткого указателя объекта материала (присутствует, если значение — не ПОСЛОЮ)
        //    ПОСЛОЮ
        ColorNumber = 62, //    Номер цвета (присутствует, если значение — не ПОСЛОЮ); ноль указывает на цвет ПОБЛОКУ (плавающий); 256 указывает на цвет ПОСЛОЮ; отрицательное значение указывает на то, что слой отключен (необязательно)
        //    ПОСЛОЮ
        LineWeight = 370, //    Значение перечня веса линий. Сохраняется и перемещается как 16-разрядное целое число.
        //    не пропускается
        LineTypeScale = 48, //    Масштаб типа линий (необязательно)
        //    1.0
        Visibility = 60, //    Видимость объекта (необязательно):
        //    0 = видимые
        //    1 = невидимые
        //    0,
        NumberOfBytes = 92, //    Количество байтов в графике объекта прокси, представленной в последующих группах с кодом 310, которые являются записями двоичного уровня (необязательно)
        //    без значения по умолчанию
        BinaryChunk = 310, //    Графика объекта прокси (несколько строк; макс. 256 символов в каждой строке) (необязательно)
        //    без значения по умолчанию
        A24bitColor = 420, //    Цветовое 24-битное значение, рассматриваемое в контексте байтов со значением от 0 до 255. Младшим байтом является синее значение, средним байтом — зеленое, а третьему байту соответствует красное значение. Высшим байтом всегда является 0. Групповой код нельзя использовать в пользовательских объектах для собственных данных, так как групповой код зарезервирован для цветовых данных уровня класса AcDbEntity и данных прозрачности уровня класса AcDbEntity
        //    без значения по умолчанию
        ColorName = 430, //    Имя цвета. Групповой код нельзя использовать в пользовательских объектах для собственных данных, так как групповой код зарезервирован для цветовых данных уровня класса AcDbEntity и данных прозрачности уровня класса AcDbEntity
        //    без значения по умолчанию
        TransparencyValue = 440, //    Значение прозрачности. Групповой код нельзя использовать в пользовательских объектах для собственных данных, так как групповой код зарезервирован для цветовых данных уровня класса AcDbEntity и данных прозрачности уровня класса AcDbEntity
        //    без значения по умолчанию
        PlotStyleID = 390, //    Идентификатор/дескриптор объекта стиля печати
        //    без значения по умолчанию
        ShadowMode = 284, //    Режим теней
        //    0 = отображение отбрасываемой и падающей теней
        //    1 = отображение отбрасываемой тени
        //    2 = отображение падающей тени
        //    3 = игнорирование теней
        //    Прим.: Это свойство является устаревшим в программных продуктах на базе AutoCAD начиная с версии 2016. Тем не менее оно поддерживается для обеспечения обратной совместимости с предыдущими версиями.
        //    без значения по умолчанию
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
//#include "seqend.h"
#include "insert.h"
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
