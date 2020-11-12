#pragma once

// https://help.autodesk.com/view/OARX/2020/RUS/?guid=GUID-235B22E0-A567-4CF6-92D3-38A2306D73F3
#include "block.h"
#include "codedata.h"
#include "dxfvalues.h"
#include "header.h"
#include <QFile>
#include <QObject>
#include <QTextStream>
#include <QVector>
#include <algorithm>

struct SectionParser;
struct LAYER;
using Layers = std::map<QString, LAYER*>;

class DxfFile : public QObject {
    Q_OBJECT
public:
    explicit DxfFile(QObject* parent = nullptr);
    ~DxfFile();
    bool read(const QString& fileName);
    static LAYER* layer(const QString& name);
    Layers layers;

private:
    int ctr = 0;
    static DxfFile* self;
    QFile file;
    QTextStream in;
    QVector<SectionParser*> sections;
    QMap<QString, Block*> blocks;
    Header header;
};
