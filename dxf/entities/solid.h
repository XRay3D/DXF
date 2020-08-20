#pragma once
#include "entity.h"
struct SOLID final : Entity {
    SOLID(SectionParser* sp);

    // Entity interface
public:
    void draw() const override;
    void drawInsert(INSERT_ET* i) const override;
    void parse(CodeData& code) override;
    Type type() const override { return Type::SOLID; }

    enum VarType {
        SubclassMarker = 100, // Маркер подкласса (AcDbTrace)

        FirstCornerX = 10, // Первая угловая точка        //        Файл DXF: значение X; приложение: 3D-точка
        FirstCornerY = 20, // Файл DXF: значения Y и Z первой угловой точки
        FirstCornerZ = 30,

        SecondCornerX = 11, // Вторая угловая точка        //        Файл DXF: значение X; приложение: 3D-точка
        SecondCornerY = 21, // Файл DXF: значения Y и Z второй угловой точки
        SecondCornerZ = 31,

        ThirdCornerX = 12, // Третья угловая точка        //        Файл DXF: значение X; приложение: 3D-точка
        ThirdCornerY = 22, // Файл DXF: значения Y и Z третьей угловой точки
        ThirdCornerZ = 32,

        FourthCornerX = 13, // , // Четвертая угловая точка. Если введены только три угловых точки для определения объекта SOLID, то четвертая и третья угловые координаты совпадают.        //        Файл DXF: значение X; приложение: 3D-точка
        FourthCornerY = 23, // Файл DXF: значения Y и Z четвертой угловой точки
        FourthCornerZ = 33,

        Thickness = 39, // Толщина (необязательно; значение по умолчанию = 0)

        ExtrDirX = 210, // Направление выдавливания (необязательно; значение по умолчанию = 0, 0, 1)        //        Файл DXF: значение X; приложение: 3D-вектор
        ExtrDirY = 220, //        Файл DXF: значения Y и Z для направления выдавливания (необязательно)
        ExtrDirZ = 230
    };
    enum Corners {
        NoCorner = 0,
        FirstCorner = 1,
        SecondCorner = 2,
        ThirdCorner = 4,
        FourthCorner = 8,
    };

    QPointF firstCorner;
    QPointF secondCorner;
    QPointF thirdCorner;
    QPointF fourthCorner;

    int corners = NoCorner;

    double thickness = 0;
    double radius = 0;
};
