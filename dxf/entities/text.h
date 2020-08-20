#pragma once
#include "entity.h"
struct TEXT final : Entity {
    TEXT(SectionParser* sp);

    // Entity interface
public:
    void draw() const override;
    void drawInsert(INSERT_ET* i) const override;
    void parse(CodeData& code) override;
    Type type() const override { return Type::TEXT; }

    enum VarType {
        SubclassMarker = 100, // Маркер подкласса (AcDbText)
        Thickness = 39, // Толщина (необязательно; значение по умолчанию = 0)
        FirstAlignmentPtX = 10, // Первая точка выравнивания (в ОСК)        //Файл DXF: значение X; приложение: 3D-точка
        FirstAlignmentPtY = 20,
        FirstAlignmentPtZ = 30, // Файл DXF: значения Y и Z первой точки выравнивания (в ОСК)
        TextHeight = 40, // Высота текста
        Text = 1, // Значение по умолчанию (сама строка)
        Rotation = 50, // Поворот текста (необязательно; значение по умолчанию = 0)
        RelativeScaleX = 41, // Относительный масштабный коэффициент по оси X: ширина (необязательно; значение по умолчанию = 1)        //Это значение также корректируется при использовании вписываемого текста
        ObliqueAngle = 51, // Угол наклона (необязательно; значение по умолчанию = 0)
        TextStyleName = 7, // Имя стиля текста (необязательно, значение по умолчанию = STANDARD)
        TextGenerationFlags = 71, // Флаги создания текста (необязательно, значение по умолчанию = 0):
        HorizontalJustType = 72, // Тип выравнивания текста по горизонтали (необязательно, значение по умолчанию = 0); целочисленные коды (не битовые):        //Подробности см. в таблице целочисленных групповых кодов 72 и 73
        VerticalJustType = 73, // Тип выравнивания текста по вертикали (необязательно, значение по умолчанию = 0); целочисленные коды (не битовые):
        SecondAlignmentPointX = 11, // Вторая точка выравнивания (в ОСК) (необязательно)        //Файл DXF: значение X; приложение: 3D-точка        //Это значение имеет смысл, только если значение групп 72 или 73 не равно нулю (если выравнивание не является выравниванием по базовой линии/слева)
        SecondAlignmentPointY = 21,
        SecondAlignmentPointZ = 31, // Файл DXF: значения Y и Z второй точки выравнивания (в ОСК) (необязательно)
        ExtrDirX = 210, // Направление выдавливания (необязательно; значение по умолчанию = 0, 0, 1)        //Файл DXF: значение X; приложение: 3D-вектор
        ExtrDirY = 220,
        ExtrDirZ = 230, // Файл DXF: значения Y и Z для направления выдавливания (необязательно)
        // SubclassMarker = 100, // Маркер подкласса (AcDbText)
        //        https : //help.autodesk.com/view/OARX/2020/RUS/?guid=GUID-62E5383D-8A14-47B4-BFC4-35824CAE8363
    };

    enum TextGenerationFlagsE { // 71
        Backward = 2, // текст в обратном направлении (зеркально отражен по X)
        UpsideDown = 4 // текст перевернут (зеркально отражен по Y)
    };

    enum HorizontalJustTypeE { // 72
        Left = 0, // слева
        Center = 1, // по центру
        Right = 2, // справа
        Aligned = 3, // параллельно (если выравнивание по вертикали = 0)
        MiddleH = 4, // посередине (если выравнивание по вертикали = 0)
        Fit = 5, // вписать (если выравнивание по вертикали = 0)
    };
    enum VerticalJustTypeE { // 73
        Baseline = 0, // по базовой линии
        Bottom = 1, // снизу
        MiddleV = 2, // посередине
        Top = 3, // сверху
    };

    QString text;
    QPointF pt1;
    QPointF pt2;

    TextGenerationFlagsE textGenerationFlags = Backward;
    HorizontalJustTypeE horizontalJustType = Left;
    VerticalJustTypeE verticalJustType = Baseline;

    double thickness = 0;
    double textHeight = 0;
};
