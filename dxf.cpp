#include "dxf.h"
#include "section.h"
#include <QDebug>
#include <QMetaEnum>

QTextStream DXF::in;

QDebug operator<<(QDebug debug, const CodeData& c)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "\rDC(" << c.code << ", " << c.rawVal << ", " << c.type << ')';
    return debug;
}

DXF::DXF(QObject* parent)
    : QObject(parent)
{
}

DXF::~DXF() { qDeleteAll(sections); }
// read извлекает указанные пары код / значение из файла DXF.
// Для этой функции требуются четыре строковых параметра,
// допустимое имя файла DXF, имя раздела DXF,
// имя объекта в этом разделе и список кодов, разделенных запятыми.

void DXF::read(const QString& fileName,
    QString strSection,
    QString strObject,
    QString strCodeList)
{
    //    Open dxfFile For Input As #1
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    in.setDevice(&file);
    //    while (!in.atEnd()) {
    //        QString line = in.readLine();
    //        process_line(line);
    //    }

    QString ReadDXF;
    QString tmpCode;
    QString lastObj;

    QVector<CodeData> codes;
    codes << ReadCodes();
    while (codes.last().rawVal != "EOF") {
        switch (Section ::key(codes.last().rawVal)) {
        case Section::HEADER:
            sections << new SectionHEADER(codes);
            break;
        case Section::CLASSES:
            sections << new SectionCLASSES(codes);
            break;
        case Section::TABLES:
            sections << new SectionTABLES(codes);
            break;
        case Section::BLOCKS:
            sections << new SectionBLOCKS(codes);
            break;
        case Section::ENTITIES:
            sections << new SectionENTITIES(codes);
            break;
        case Section::OBJECTS:
            sections << new SectionOBJECTS(codes);
            break;
        case Section::THUMBNAILIMAGE:
            sections << new SectionTHUMBNAILIMAGE(codes);
            break;
        default:
            //throw codes.last().rawVal;
            break;
        }
        if (!sections.isEmpty() && sections.last()->data.size() < 3)
            sections.last()->parse();
        codes << ReadCodes();
    }
    //    // Получите первую пару код / значение
    //    auto codes = ReadCodes();
    //    section->data << codes;
    //    // Прокрутите весь файл до строки "EOF"
    //    while (codes.rawVal != "EOF") {
    //        // если код группы «0» и значение «SECTION» ..
    //        if (codes.code == 0 && codes.rawVal == "SECTION") {
    //            // Это должен быть новый раздел, поэтому получите следующую пару код / значение.
    //            codes = ReadCodes();
    //            section->data << codes;
    //            section->type = static_cast<Section::sec>(section.staticMetaObject.enumerator(0).keyToValue(codes.sVal.toStdString().data()));
    //            strSection = codes.rawVal; ///////////// для отладки
    //            // если этот раздел правильный ..
    //            if (codes.rawVal == strSection) {
    //                // Получите следующую пару код / значение и ..
    //                codes = ReadCodes();
    //                section->data << codes;
    //                // Прокрутите этот раздел до тех пор, пока не появится надпись «ENDSEC».
    //                while (codes.rawVal != "ENDSEC") {
    //                    // В разделе все коды «0» обозначают объект. если вы найдете «0», сохраните имя объекта для будущего использования.
    //                    if (codes.code == 0)
    //                        lastObj = codes.rawVal;
    //                    // если этот объект вас интересует
    //                    if (lastObj == strObject) {
    //                        // Обведите код запятыми
    //                        tmpCode = "," + QString::number(codes.code) + ",";
    //                        // если этот код есть в списке кодов ..
    //                        if (strCodeList.indexOf(tmpCode, 0, Qt::CaseInsensitive) > -1) {
    //                            // Добавьте возвращаемое значение.
    //                            ReadDXF = ReadDXF + codes.code + "=" + codes.rawVal + '\r';
    //                        }
    //                    }
    //                    // Прочитать другую пару код / значение
    //                    codes = ReadCodes();
    //                    section->data << codes;
    //                }
    //                sections << section;
    //                section = {}; //clear
    //            }
    //        } else {
    //            codes = ReadCodes();
    //            section->data << codes;
    //        }
    //    }
    file.close();
    for (Section* s : sections) {
        qDebug() << (*s);
    }
}

// ReadCodes reads two lines from an open file and returns a two item
// array, a group code and its value. As long as a DXF file is read
// two lines at a time, all should be fine. However, to make your
// code more reliable, you should add some additional error and
// other checking.
CodeData DXF::ReadCodes()
{
    QString codeStr, valStr;
    codeStr = in.readLine();
    valStr = in.readLine();
    CodeData ret { codeStr.toInt(), valStr };
    return ret;
}

int Section::key(const QString& key)
{
    return staticMetaObject.enumerator(0).keysToValue(key.toLocal8Bit().data());
}