#include "dxf.h"
#include "section/entities.h"
#include "section/sectionparser.h"
#include <QDebug>
#include <dxf/section/blocks.h>
#include <dxf/section/classes.h>
#include <dxf/section/headerparser.h>
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

bool DxfFile::read(const QString& fileName)
{
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    in.setDevice(&file);

    int ctr = 0;
    QVector<CodeData> codes;
    do {
        codes.append({ in.readLine().toInt(), in.readLine(), ctr });
        ctr += 2;
        qDebug() << codes.last();
        if (codes.last() == "ENDSEC") {
            int bsec = 0;
            while (codes[bsec++] != "SECTION" && bsec < codes.size())
                continue;
            switch (SectionParser::key(QString(codes[bsec]))) {
            case SectionParser::HEADER:
                sections << new SectionHEADER(header, std::move(codes));
                break;
            case SectionParser::CLASSES:
                sections << new SectionCLASSES(std::move(codes));
                break;
            case SectionParser::TABLES:
                sections << new SectionTABLES(layers, std::move(codes));
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
                //throw codes.last();
                break;
            }
            if (sections.size())
                sections.last()->parse();
        }
    } while (!in.atEnd() || codes.last() != "EOF");

    file.close();
    for (SectionParser* s : sections) {
        qDebug() << (*s);
    }
    return true;
}
