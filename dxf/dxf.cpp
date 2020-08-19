#include "dxf.h"
#include "section/section.h"
#include "section/sectionentities.h"
#include <QDebug>
#include <QMetaEnum>
#include <dxf/section/sectionblocks.h>
#include <dxf/section/sectionclasses.h>
#include <dxf/section/sectionheader.h>
#include <dxf/section/sectionobjects.h>
#include <dxf/section/sectiontables.h>
#include <dxf/section/sectionthumbnailimage.h>

QTextStream DxfFile::in;

DxfFile::DxfFile(QObject* parent)
    : QObject(parent)
{
}

DxfFile::~DxfFile() { qDeleteAll(sections); }
// read извлекает указанные пары код / значение из файла DXF.
// Для этой функции требуются четыре строковых параметра,
// допустимое имя файла DXF, имя раздела DXF,
// имя объекта в этом разделе и список кодов, разделенных запятыми.

void DxfFile::read(const QString& fileName,
    QString /*strSection*/,
    QString /*strObject*/,
    QString /*strCodeList*/)
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
        switch (SectionParser ::key(codes.last().rawVal)) {
        case SectionParser::HEADER:
            sections << new SectionHEADER(header, codes);
            sections.last()->parse();
            break;
        case SectionParser::CLASSES:
            sections << new SectionCLASSES(codes);
            sections.last()->parse();
            break;
        case SectionParser::TABLES:
            sections << new SectionTABLES(codes);
            sections.last()->parse();
            break;
        case SectionParser::BLOCKS:
            sections << new SectionBLOCKS(codes);
            sections.last()->parse();
            break;
        case SectionParser::ENTITIES:
            sections << new SectionENTITIES(codes);
            sections.last()->parse();
            break;
        case SectionParser::OBJECTS:
            sections << new SectionOBJECTS(codes);
            sections.last()->parse();
            break;
        case SectionParser::THUMBNAILIMAGE:
            sections << new SectionTHUMBNAILIMAGE(codes);
            sections.last()->parse();
            break;
        default:
            //throw codes.last().rawVal;
            break;
        }
        //        if (!sections.isEmpty() && sections.last()->data.size() < 3)
        //            sections.last()->parse();
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
    for (SectionParser* s : sections) {
        qDebug() << (*s);
    }
}

// ReadCodes reads two lines from an open file and returns a two item
// array, a group code and its value. As long as a DXF file is read
// two lines at a time, all should be fine. However, to make your
// code more reliable, you should add some additional error and
// other checking.
CodeData DxfFile::ReadCodes()
{
    QString codeStr, valStr;
    codeStr = in.readLine();
    valStr = in.readLine();
    CodeData ret { codeStr.toInt(), valStr };
    return ret;
}

int SectionParser::key(const QString& key)
{
    return staticMetaObject.enumerator(0).keysToValue(key.toLocal8Bit().data());
}
