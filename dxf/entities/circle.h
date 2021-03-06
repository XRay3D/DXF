#pragma once

#include "entity.h"

struct CIRCLE final : Entity {
    CIRCLE(SectionParser* sp);

    // Entity interface
public:
    void draw(const INSERT_ET* const i = nullptr) const override;
    void parse(CodeData& code) override;
    Type type() const override { return Type::CIRCLE; }

    enum VarType {
        SubclassMarker = 100, // Маркер подкласса (AcDbCircle)
        Thickness = 39, // Толщина (необязательно; значение по умолчанию = 0)
        CenterPointX = 10, // Центральная точка (в ОСК)
        // Файл DXF: значение X; приложение: 3D-точка
        CenterPointY = 20,
        CenterPointZ = 30, // Файл DXF: значения Y и Z для центральной точки (в ОСК)
        Radius = 40, // Радиус
        ExtrDirX = 210, // Направление выдавливания (необязательно; значение по умолчанию = 0, 0, 1)       // Файл DXF: значение X; приложение: 3D-вектор
        ExtrDirY = 220, // Файл DXF: значения Y и Z для направления выдавливания (необязательно)
        ExtrDirZ = 230,
    };
    QPointF centerPoint;
    double thickness = 0;
    double radius = 0;
};
