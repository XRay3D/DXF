#ifndef DXF_H
#define DXF_H

#include "codedata.h"
#include <QFile>
#include <QObject>
#include <QTextStream>
#include <QVector>
#include <algorithm>

struct Section;

class DXF : public QObject {
    Q_OBJECT
public:
    explicit DXF(QObject* parent = nullptr);
    ~DXF();
    void read(const QString& fileName, QString strSection = {}, QString strObject = {}, QString strCodeList = {});
    static CodeData ReadCodes();

private:
    QFile file;
    static QTextStream in;
    QVector<Section*> sections;

signals:
};

#endif // DXF_H
