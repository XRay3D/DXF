#include "layer.h"

#include <QGraphicsScene>

extern QGraphicsScene* scene;

LAYER::LAYER(SectionParser* sp)
    : TableItem(sp)
{
    scene->addItem(gig = new QGraphicsItemGroup);
}

void LAYER::parse(CodeData& code)
{
    do {
        data << code;
        switch (code.code) {
        case SubclassMarker:
            break;
        case LayerName:
            name = code.getString();
            break;
        case Flags:
            flags = code.getInteger();
            break;
        case ColorNumber:
            colorNumber = code.getInteger();
            break;
        case LineTypeName:
            lineTypeName = code.getString();
            break;
        case PlottingFlag:
            plottingFlag = code.getInteger();
            break;
        case LineWeightEnum:
            lineWeightEnum = code.getInteger();
            break;
        case PlotStyleNameID:
            break;
        case MaterialID:
            break;
        }
        code = sp->nextCode();
    } while (code.code != 0);
}
