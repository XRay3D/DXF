#include "dxf.h"
#include "section/entities.h"
#include "section/sectionparser.h"
#include <QDebug>
#include <dxf/section/blocks.h>
#include <dxf/section/classes.h>
#include <dxf/section/header.h>
#include <dxf/section/objects.h>
#include <dxf/section/tables.h>
#include <dxf/section/thumbnailimage.h>

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
    int ctr = 0;
    QVector<CodeData> codes;
    do {
        QString codeStr(in.readLine());
        QString valStr(in.readLine());
        codes.append({ codeStr.toInt(), valStr, ctr += 2 });
        if (codes.last().rawVal == "ENDSEC") {
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
                sections << new SectionBLOCKS(blocks, std::move(codes));
                break;
            case SectionParser::ENTITIES:
                sections << new SectionENTITIES(blocks, std::move(codes));
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
