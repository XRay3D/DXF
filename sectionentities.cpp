#include "sectionentities.h"
#include "dxf.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMetaEnum>
#include <QMetaObject>

extern QGraphicsScene* scene;

SectionENTITIES::SectionENTITIES(const QVector<CodeData>& data)
    : Section(data)
{
}

void SectionENTITIES::parse()
{
    qDebug(Q_FUNC_INFO);
    CodeData code;
    QString key;
    while (code.rawVal != "ENDSEC") {
        // Прочитать другую пару код / значение
        code = DXF::ReadCodes();
        data << code;
        if (code.rawVal == "ENDSEC") {
            break;
        } else if (staticMetaObject.enumerator(1).keyToValue(code.rawVal.toLocal8Bit().toUpper().data()) > -1) {
            key = code.rawVal;
            entities[key].resize(entities[key].size() + 1);
        }
        entities[key].last() << code;
    }
    for (auto [key, val] : entities) {
        qDebug() << key << val.size();
    }
    /*
"HATCH" 242
"INSERT" 15455
"LINE" 16
"LWPOLYLINE" 9562
"SOLID" 1266
"TEXT" 186
*/
    {
        for (auto& val : entities["LINE"]) {
            QMap<int, double> values;
            for (auto& data : val) {
                if (data.type == CodeData::Double)
                    values[data.code] = std::get<double>(data._val);
                else if (data.type == CodeData::Integer)
                    values[data.code] = std::get<qint64>(data._val);
            }
            scene->addLine({ { values[10], values[20] }, { values[11], values[21] } }, QPen(Qt::black, 0.0));
        }
    }
    {
        for (auto& val : entities["LWPOLYLINE"]) {
            QPolygonF poly;
            int counter = 0;
            for (auto& data : val) {
                if (data.code == 90) {
                    poly.resize(std::get<qint64>(data._val));
                } else if (data.code == 10) {
                    poly[counter].rx() = std::get<double>(data._val);
                } else if (data.code == 20) {
                    poly[counter].ry() = std::get<double>(data._val);
                    ++counter;
                }
            }
            scene->addPolygon(poly, QPen(Qt::red, 0.0), Qt::NoBrush);
        }
    }
    {
        for (auto& val : entities["SOLID"]) {
            QPolygonF poly;
            QPointF pt;
            for (auto& data : val) {
                if (data.code == 10) {
                    pt.rx() = std::get<double>(data._val);
                } else if (data.code == 20) {
                    pt.ry() = std::get<double>(data._val);
                    poly.append(pt);
                } else if (data.code == 11) {
                    pt.rx() = std::get<double>(data._val);
                } else if (data.code == 21) {
                    pt.ry() = std::get<double>(data._val);
                    poly.append(pt);
                }
            }
            scene->addPolygon(poly, QPen(Qt::green, 0.0), Qt::NoBrush);
        }
    }

    scene->setSceneRect(scene->itemsBoundingRect());
    reinterpret_cast<QGraphicsView*>(scene->parent())->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    qDebug() << scene;
}
