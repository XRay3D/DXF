#include "text.h"
#include "insert.h"
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPainter>

extern QGraphicsScene* scene;

class TextItem final : public QGraphicsItem {
    const TEXT* text;
    QPainterPath path;
    QColor color;

public:
    TextItem(const TEXT* text, const QColor& color)
        : text(text)
        , color(color)
    {
        QFont f("Input Mono");
        f.setPointSizeF(text->textHeight);

        path.addText(text->pt2, f, text->text);
        text->pt2 + QPointF(-3, -1);
    }
    ~TextItem() = default;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override
    {
        return path.boundingRect();
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) override
    {
        painter->setPen({ color, 0.0 });
        //painter->setPen(Qt::NoPen);
        painter->setBrush(color);
        //painter->drawPath(path);

        {
            QFont f("Input");
            f.setPointSizeF(text->textHeight * 0.8);
            painter->setFont(f);
        }
        painter->save();
        painter->scale(1, -1);
        //painter->translate(0, text->pt2.x());
        painter->drawText(QPointF(text->pt2.x(), -text->pt2.y()), text->text);
        painter->restore();
    }
};

TEXT::TEXT(SectionParser* sp)
    : Entity(sp)
{
}

void TEXT::draw() const
{
    auto item = new TextItem(this, color());
    scene->addItem(item);
    attachToLayer(item);
}

void TEXT::drawInsert(INSERT_ET* i) const
{
    Q_UNUSED(i)
}

void TEXT::parse(CodeData& code)
{
    do {
        switch (code.code) {
        case SubclassMarker:
            break;
        case Thickness:
            thickness = code.getDouble();
            break;
        case FirstAlignmentPtX:
            pt1.rx() = code.getDouble();
            break;
        case FirstAlignmentPtY:
            pt1.ry() = code.getDouble();
            break;
        case FirstAlignmentPtZ:
            break;
        case TextHeight:
            textHeight = code.getDouble();
            break;
        case Text:
            text = code.getString();
            break;
        case Rotation:
            break;
        case RelativeScaleX:
            break;
        case ObliqueAngle:
            break;
        case TextStyleName:
            break;
        case TextGenerationFlags:
            textGenerationFlags = static_cast<TextGenerationFlagsE>(code.getInteger());
            break;
        case HorizontalJustType:
            horizontalJustType = static_cast<HorizontalJustTypeE>(code.getInteger());
            break;
        case VerticalJustType:
            verticalJustType = static_cast<VerticalJustTypeE>(code.getInteger());
            break;
        case SecondAlignmentPointX:
            pt2.rx() = code.getDouble();
            break;
        case SecondAlignmentPointY:
            pt2.ry() = code.getDouble();
            break;
        case SecondAlignmentPointZ:
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
