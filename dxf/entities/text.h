#pragma once
#include "entity.h"
struct TEXT final : Entity {
    TEXT();

    // Entity interface
public:
    void draw() const override;
    void parse(CodeData& code) override;
  /*
Text group codes
Group
code Description
100 Subclass marker (AcDbText)
39 Thickness (optional; default = 0)
10 First alignment point (in OCS)
DXF: X value; APP: 3D point
20, 30 DXF: Y and Z values of first alignment point (in OCS)
40 Text height
1 Default value (the string itself)
50 Text rotation (optional; default = 0)
41 Relative X scale factor—width (optional; default = 1)
This value is also adjusted when fit-type text is used
51 Oblique angle (optional; default = 0)
7 Text style name (optional, default = STANDARD)
71 Text generation flags (optional, default = 0):
2 = Text is backward (mirrored in X)
4 = Text is upside down (mirrored in Y)
72 Horizontal text justification type (optional, default = 0) integer
codes (not bit-coded)
0 = Left; 1= Center; 2 = Right
3 = Aligned (if vertical alignment = 0)
4 = Middle (if vertical alignment = 0)
5 = Fit (if vertical alignment = 0)
See the Group 72 and 73 integer codes table for clarification
11 Second alignment point (in OCS) (optional)
DXF: X value; APP: 3D point
This value is meaningful only if the value of a 72 or 73 group is
nonzero (if the justification is anything other than baseline/left)
21, 31 DXF: Y and Z values of second alignment point (in OCS)
(optional)
210 Extrusion direction (optional; default = 0, 0, 1)
DXF: X value; APP: 3D vector
220, 230 DXF: Y and Z values of extrusion direction (optional)
100 Subclass marker (AcDbText)
73 Vertical text justification type (optional, default = 0): integer
codes (not bit-coded):
0 = Baseline; 1 = Bottom; 2 = Middle; 3 = Top
See the Group 72 and 73 integer codes table for clarification
The following table describes the group codes 72 (horizontal alignment) and 73
(vertical alignment) in greater detail.
Group 72 and 73 integer codes
Group 73
Group
72
0
1 2 3 4 5
3 (top) TLeft TCenter TRight
2 (middle) MLeft MCenter MRight
1 (
bottom)
BLeft BCenter BRight
0 (
baseline)
Left Center Right Aligned Middle Fit
If group 72




TEXT (DXF)
К объектам текста применяются следующие групповые коды.

Групповые коды текста

Групповой код

Описание

100

Маркер подкласса (AcDbText)

39

Толщина (необязательно; значение по умолчанию = 0)

10

Первая точка выравнивания (в ОСК)

Файл DXF: значение X; приложение: 3D-точка

20, 30

Файл DXF: значения Y и Z первой точки выравнивания (в ОСК)

40

Высота текста

1

Значение по умолчанию (сама строка)

50

Поворот текста (необязательно; значение по умолчанию = 0)

41

Относительный масштабный коэффициент по оси X: ширина (необязательно; значение по умолчанию = 1)

Это значение также корректируется при использовании вписываемого текста

51

Угол наклона (необязательно; значение по умолчанию = 0)

7

Имя стиля текста (необязательно, значение по умолчанию = STANDARD)

71

Флаги создания текста (необязательно, значение по умолчанию = 0):

2 = текст в обратном направлении (зеркально отражен по X)

4 = текст перевернут (зеркально отражен по Y)

72

Тип выравнивания текста по горизонтали (необязательно, значение по умолчанию = 0); целочисленные коды (не битовые):

0 = слева

1 = по центру

2 = справа

3 = параллельно (если выравнивание по вертикали = 0)

4 = посередине (если выравнивание по вертикали = 0)

5 = вписать (если выравнивание по вертикали = 0)

Подробности см. в таблице целочисленных групповых кодов 72 и 73

11

Вторая точка выравнивания (в ОСК) (необязательно)

Файл DXF: значение X; приложение: 3D-точка

Это значение имеет смысл, только если значение групп 72 или 73 не равно нулю (если выравнивание не является выравниванием по базовой линии/слева)

21, 31

Файл DXF: значения Y и Z второй точки выравнивания (в ОСК) (необязательно)

210

Направление выдавливания (необязательно; значение по умолчанию = 0, 0, 1)

Файл DXF: значение X; приложение: 3D-вектор

220, 230

Файл DXF: значения Y и Z для направления выдавливания (необязательно)

100

Маркер подкласса (AcDbText)

73

Тип выравнивания текста по вертикали (необязательно, значение по умолчанию = 0); целочисленные коды (не битовые):

0 = по базовой линии

1 = снизу

2 = посередине

3 = сверху

Подробности см. в таблице целочисленных групповых кодов 72 и 73

В следующей таблице подробно описываются групповые коды 72 (выравнивание по горизонтали) и 73 (выравнивание по вертикали).

Целочисленные групповые коды 72 и 73

Группа с кодом 73

Группа с кодом 72

0

1

2

3

4

5

3 (сверху)

ВЛ

ВЦ

ВП

2 (посередине)

СЛ

СЦ

СП

1 (снизу)

НЛ

НЦ

НП

0 (по базовой линии)

Левая

Центр

Справа

Параллельный

Середина

По ширине



https://help.autodesk.com/view/OARX/2020/RUS/?guid=GUID-62E5383D-8A14-47B4-BFC4-35824CAE8363


*/


//    enum VarType {
//        SubclassMarker = 100, // Маркер подкласса (AcDbCircle)
//        Thickness = 39, // Толщина (необязательно; значение по умолчанию = 0)
//        CenterPointX = 10, // Центральная точка (в ОСК)
//        // Файл DXF: значение X; приложение: 3D-точка
//        CenterPointY = 20,
//        CenterPointZ = 30, // Файл DXF: значения Y и Z для центральной точки (в ОСК)
//        Radius = 40, // Радиус
//        ExtrDirX = 210, // Направление выдавливания (необязательно; значение по умолчанию = 0, 0, 1)
//        // Файл DXF: значение X; приложение: 3D-вектор
//        ExtrDirY = 220,
//        ExtrDirZ = 230, // Файл DXF: значения Y и Z для направления выдавливания (необязательно)
//    };
//    QPointF centerPoint;
//    double thickness = 0;
//    double radius = 0;

};
