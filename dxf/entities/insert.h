#pragma once

#include "entity.h"
#include <set>

struct INSERT final : Entity {
    INSERT();

    // Entity interface
public:
    void draw() const override;
    void parse(CodeData& code) override;

    enum VarType {
        SubclassMrker = 100, // Subclass marker (AcDbBlockReference)
        var66 = 66, /* Variable attributes-follow flag (optional; default = 0);
                         if the value of attributes-follow flag is 1,
                         a series of attribute entities is expected to follow the insert, terminated by a seqend entity*/
        BlockName = 2, // Block name
        InsPtX = 10, // Insertion point (in OCS) // DXF: X value; APP: 3D point
        InsPtY = 20, // DXF: Y value of insertion point (in OCS)
        InsPtZ = 30, // DXF: Z value of insertion point (in OCS)
        ScaleX = 41, // X scale factor (optional; default = 1)
        ScaleY = 42, // Y scale factor (optional; default = 1)
        ScaleZ = 43, // Z scale factor (optional; default = 1)
        RotationAngle = 50, // Rotation angle (optional; default = 0)
        ColCount = 70, // Column count (optional; default = 1)
        RowCount = 71, // Row count (optional; default = 1)
        ColSpacing = 44, // Column spacing (optional; default = 0)
        RowSpacing = 45, // Row spacing (optional; default = 0)
        ExtrDirX = 210, // Extrusion direction (optional; default = 0, 0, 1) // DXF: X value; APP: 3D vector
        ExtrDirY = 220, // DXF: Y value of extrusion direction (optional)
        ExtrDirZ = 230, // DXF: Z value of extrusion direction (optional)
    };

    const std::set<VarType> checker;
    std::map<VarType, var&> vars;
    //QMap<VarType, var&> vars;

    //    var val100; // Маркер подкласса (AcDbBlockReference)
    //    var val66; // Флаг следования атрибутов переменной (необязательно; значение по умолчанию = 0); если значение флага перемещения атрибута — 1, за вставкой следует ряд объектов атрибута, заканчивающийся объектом SEQEND
    //    var val2; // Block name
    //    var val10; // Точка вставки (в ОСК). Файл DXF: значение X; приложение: 3D-точка
    //    var val20, val30; // Файл DXF: значение Y и Z точки вставки (в ОСК)
    //    var val41; // Масштабный коэффициент по оси X (необязательно; значение по умолчанию = 1)
    //    var val42; // Масштабный коэффициент по оси Y (необязательно; значение по умолчанию = 1)
    //    var val43; // Масштабный коэффициент по оси Z (необязательно; значение по умолчанию = 1)
    //    var val50; // Угол поворота (необязательно; значение по умолчанию = 0)
    //    var val70; // Количество столбцов (необязательно; значение по умолчанию = 1)
    //    var val71; // Количество рядов (необязательно; значение по умолчанию = 1)
    //    var val44; // Интервал между столбцами (необязательно; значение по умолчанию = 0)
    //    var val45; // Интервал между строками (необязательно; значение по умолчанию = 0)
    //    var val210; // Направление выдавливания (необязательно; значение по умолчанию = 0, 0, 1). Файл DXF: значение X; приложение: 3D-вектор
    //    var val220, val230; // Файл DXF: значения Y и Z для направления выдавливания (необязательно)
};
