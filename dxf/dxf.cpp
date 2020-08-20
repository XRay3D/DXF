#include "dxf.h"
#include "section/sectionentities.h"
#include "section/sectionparser.h"
#include <QDebug>
#include <dxf/section/sectionblocks.h>
#include <dxf/section/sectionclasses.h>
#include <dxf/section/sectionheader.h>
#include <dxf/section/sectionobjects.h>
#include <dxf/section/sectiontables.h>
#include <dxf/section/sectionthumbnailimage.h>

DxfFile* DxfFile::self;

DxfFile::DxfFile(QObject* parent)
    : QObject(parent)
{
    self = this;
}

DxfFile::~DxfFile() { qDeleteAll(sections); }

void DxfFile::read(const QString& fileName)
{

    //    Open dxfFile For Input As #1
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    in.setDevice(&file);
    //    while (!in.atEnd()) {
    //    }

    QVector<CodeData> codes;
    do {
        QString codeStr(in.readLine());
        QString valStr(in.readLine());
        codes.append({ codeStr.toInt(), valStr });
        if (codes.last().rawVal == "ENDSEC") {
            qDebug() << codes[0];
            qDebug() << codes[1];
            qDebug() << codes.last();
            qDebug("\n");
            switch (SectionParser::key(codes[1].rawVal)) {
            case SectionParser::HEADER:
                sections << new SectionHEADER(header, std::move(codes));
                break;
            case SectionParser::CLASSES:
                sections << new SectionCLASSES(std::move(codes));
                break;
            case SectionParser::TABLES:
                sections << new SectionTABLES(std::move(codes));
                break;
            case SectionParser::BLOCKS:
                sections << new SectionBLOCKS(std::move(codes));
                break;
            case SectionParser::ENTITIES:
                sections << new SectionENTITIES(std::move(codes));
                break;
            case SectionParser::OBJECTS:
                sections << new SectionOBJECTS(std::move(codes));
                break;
            case SectionParser::THUMBNAILIMAGE:
                sections << new SectionTHUMBNAILIMAGE(std::move(codes));
                break;
            default:
                //throw codes.last().rawVal;
                break;
            }
            sections.last()->parse();
        }
    } while (!in.atEnd() || codes.last().rawVal != "EOF");

    file.close();
    for (SectionParser* s : sections) {
        qDebug() << (*s);
    }
}
