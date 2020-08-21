#include "insert.h"
#include <QGraphicsScene>
//#include <dxf/dxf.h>

extern QGraphicsScene* scene;

INSERT_ET::INSERT_ET(QMap<QString, Block*>& blocks, SectionParser* sp)
    : Entity(sp)
    , blocks(blocks)
{
}

void INSERT_ET::draw() const
{
    if (blocks.contains(blockName)) {
        for (auto e : blocks[blockName]->entities) {
            e->drawInsert(const_cast<INSERT_ET*>(this));
        }
        if (blocks[blockName]->entities.isEmpty())
            scene->addEllipse({ insPt - QPointF(0.5, 0.5), insPt + QPointF(0.5, 0.5) }, QPen(QColor(255, 0, 0, 100), 0.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QColor(255, 0, 0));
    }
}

void INSERT_ET::drawInsert(INSERT_ET* i) const
{
    if (blocks.contains(blockName)) {
        for (auto e : blocks[blockName]->entities) {
            e->drawInsert(const_cast<INSERT_ET*>(i));
        }
        if (blocks[blockName]->entities.isEmpty())
            scene->addEllipse({ insPt - QPointF(0.5, 0.5), insPt + QPointF(0.5, 0.5) }, QPen(QColor(255, 0, 0, 100), 0.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QColor(255, 0, 0));
    }
}

void INSERT_ET::parse(CodeData& code)
{
    do {
        data << code;
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
        code = sp->nextCode();
    } while (code.code != 0);
    code = sp->prevCode();
}
