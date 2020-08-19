#pragma once

#include "codedata.h"
#include <QVector>

struct DxfBlock {
    DxfBlock();
    enum {
        B0 = 0, // Тип объекта(BLOCK)
        B5 = 5, // Дескриптор
        B102 = 102, // Начало определенной приложением группы "{имя_приложения". Например, "{ACAD_REACTORS" обозначает начало группы постоянных реакторов AutoCAD (необязательно)
        //коды, определенные в приложении == Коды и значения в пределах группы с кодом 102 определяются в прилож
        //B102 = 102, //Конец группы, "}" (необязательно)
        B330 = 330, // Идентификатор/дескриптор символьного указателя на объект владельца
        B100 = 100, // Маркер подкласса (AcDbEntity)
        B8 = 8, // Имя слоя
        //B100 = 100, // Маркер подкласса (AcDbBlockBegin)
        B2 = 2, // Имя блока
        B70 = 70, /* Флаги типа блока (кодовые битовые значения, могут быть скомбинированы):
                     0 = ни один из следующих флагов не применяется
                     1 = это анонимный блок, созданный с помощью штриховки, нанесения ассоциативных размеров, других внутренних операций или приложения
                     2 = этот блок содержит непостоянные определения атрибутов (данный бит не задается, если блок содержит все определения атрибутов, которые являются постоянными, или вовсе не содержит определений атрибутов)
                     4 = этот блок является внешней ссылкой
                     8 = этот блок является наложением внешней ссылки
                     16 = этот блок является зависимым извне
                     32 = это разрешенная внешняя ссылка или ссылка, зависимая от внешней ссылки (игнорируется при вводе)
                     64 = это определение является связанной внешней ссылкой (игнорируется при вводе) */
        B10 = 10, //Базовая точка Файл DXF: значение X; приложение: 3D-точка
        B20 = 20,
        B30 = 30, // Файл DXF: значение Y и Z базовой точки
        B3 = 3, // Имя блока
        B1 = 1, // Имя пути внешней ссылки
        B4 = 4, // Описание блока (необязательно)
    };

    inline DxfBlock& operator<<(const CodeData& cd)
    {
        if (cd.rawVal == "BLOCK" || cd.rawVal == "ENDBLK")
            return *this;
        if (bs && cd.code) {
            bData.append(cd);
        } else {
            bs = false;
            data.append(cd);
        }
        return *this;
    }
    bool bs = true;
    QVector<CodeData> bData;
    QVector<CodeData> data;
};