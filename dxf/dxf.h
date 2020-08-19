#pragma once

// https://help.autodesk.com/view/OARX/2020/RUS/?guid=GUID-235B22E0-A567-4CF6-92D3-38A2306D73F3

#include "codedata.h"
#include "dxfheader.h"
#include <QFile>
#include <QObject>
#include <QTextStream>
#include <QVector>
#include <algorithm>

struct SectionParser;

class DxfFile : public QObject {
    Q_OBJECT
public:
    explicit DxfFile(QObject* parent = nullptr);
    ~DxfFile();
    void read(const QString& fileName, QString strSection = {}, QString strObject = {}, QString strCodeList = {});
    static CodeData ReadCodes(bool retract = false);

private:
    static DxfFile* self;
    QFile file;
    QTextStream in;
    QVector<SectionParser*> sections;
    QVector<CodeData> cd;
    DxfHeader header;

signals:
};
