#include "insert.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
//#include <dxf/dxf.h>

extern QGraphicsScene* scene;

INSERT_ET::INSERT_ET(QMap<QString, Block*>& blocks, SectionParser* sp)
    : Entity(sp)
    , blocks(blocks)
{
}

void INSERT_ET::draw(const INSERT_ET* const i) const
{
    if (!blocks.contains(blockName))
        return;

    if (blocks[blockName]->entities.isEmpty())
        return;

    for (auto e : blocks[blockName]->entities) {
        if (i) {
            INSERT_ET t(*this);
            if (layerName == "0")
                t.layerName = i->layerName;
            if (insPt.isNull())
                t.insPt = i->insPt;

            if (qFuzzyIsNull(rotationAngle))
                t.rotationAngle = i->rotationAngle;

            if (e->type() != INSERT) {
                if (t.layerName == "0")
                    t.layerName = e->layerName;
            }
            e->draw(&t);
        } else if (e->type() != INSERT) {
            INSERT_ET t(*this);
            if (t.layerName == "0")
                t.layerName = e->layerName;
            e->draw(&t);
        } else {
            e->draw(this);
        }
    }
}

void INSERT_ET::parse(CodeData& code)
{
    data << code;
    do {
        switch (code.code) {
        case SubclassMrker:
            break;
        case var66:
            break;
        case BlockName:
            blockName = code.getString();
            break;
        case InsPtX:
            insPt.rx() = code.getDouble();
            break;
        case InsPtY:
            insPt.ry() = code.getDouble();
            break;
        case InsPtZ:
            break;
        case ScaleX:
            scaleX = code.getDouble();
            break;
        case ScaleY:
            scaleY = code.getDouble();
            break;
        case ScaleZ:
            break;
        case RotationAngle:
            rotationAngle = code.getDouble();
            break;
        case ColCount:
            colCount = code.getInteger();
            break;
        case RowCount:
            rowCount = code.getInteger();
            break;
        case ColSpacing:
            colSpacing = code.getDouble();
            break;
        case RowSpacing:
            rowSpacing = code.getDouble();
            break;
        case ExtrDirX:
            break;
        case ExtrDirY:
            break;
        case ExtrDirZ:
            break;
        default:
            parseEntity(code);
        }
        data << (code = sp->nextCode());
    } while (code.code != 0);
}

void INSERT_ET::transform(QGraphicsItem* item, QPointF tr) const
{
    item->setRotation(rotationAngle);
    item->setScale(scaleX /*, i->scaleY*/);
    item->setPos(insPt + tr);
}
