#pragma once
#include "entity.h"
struct LINE final : Entity {
    LINE(SectionParser* sp);

    // Entity interface
public:
    void draw() const override;
    void drawInsert(INSERT_ET* i) const override { Q_UNUSED(i) }

    void parse(CodeData& code) override;
    Type type() const override { return Type::LINE; }

    enum VarType {
        SubclassMarker = 100, // Маркер подкласса (AcDbLine)
        Thickness = 39, // Толщина (необязательно; значение по умолчанию = 0)
        StartPointX = 10, // Начальная точка (в МСК)  //Файл DXF: значение X; приложение: 3D-точка
        StartPointY = 20, // Файл DXF: значения Y и Z для начальной точки (в МСК)
        StartPointZ = 30,
        EndPointX = 11, // Конечная точка (в МСК)//Файл DXF: значение X; приложение: 3D-точка
        EndPointY = 21, // Файл DXF: значения Y и Z конечной точки (в МСК)
        EndPointZ = 31,
        ExtrDirX = 210, // Направление выдавливания (необязательно; значение по умолчанию = 0, 0, 1)//Файл DXF: значение X; приложение: 3D-вектор
        ExtrDirY = 220, //  Файл DXF: значения Y и Z для направления выдавливания (необязательно)
        ExtrDirZ = 230,
    };

    QPointF startPoint;
    QPointF endPoint;
    double thickness = 0;
};
