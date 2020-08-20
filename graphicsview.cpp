#include "graphicsview.h"

#include <QGLWidget>
#include <QScrollBar>
#include <QWheelEvent>

GraphicsView::GraphicsView(QWidget* parent)
    : QGraphicsView(parent)
{

    setCacheMode(/*CacheBackground*/ CacheNone);
    setOptimizationFlag(DontSavePainterState);
    setOptimizationFlag(DontAdjustForAntialiasing);

#if (QT_VERSION < QT_VERSION_CHECK(5, 14, 0))
    setOptimizationFlag(DontClipPainter);
#else
#endif

    setViewportUpdateMode(FullViewportUpdate);
    setDragMode(RubberBandDrag);
    setInteractive(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    //    setViewport(settings.value("chbxOpenGl").toBool()
    //            ? new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::AlphaChannel | QGL::Rgba))
    //            : new QWidget);
    setRenderHint(QPainter::Antialiasing, true);
    scale(1.0, -1.0); //flip vertical

    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::AlphaChannel | QGL::Rgba)));
    ////////////////////////////////////
}

double GraphicsView::getScale()
{
    return transform().m11();
}

void GraphicsView::zoomIn()
{
    //    if (getScale() > 10000.0)
    //        return;
    scale(zoomFactor, zoomFactor);
}

void GraphicsView::zoomOut()
{
    //    if (getScale() < 1.0)
    //        return;
    scale(1.0 / zoomFactor, 1.0 / zoomFactor);
}

void GraphicsView::wheelEvent(QWheelEvent* event)
{
    const int scbarScale = 3;

    const auto delta = event->angleDelta().y();

#if (QT_VERSION < QT_VERSION_CHECK(5, 14, 0))
    const auto pos = event->pos();
#else
    const auto pos = event->position().toPoint();
#endif

    switch (event->modifiers()) {
    case Qt::ControlModifier:
        if (abs(delta) == 120) {
            setInteractive(false);
            if (delta > 0)
                zoomIn();
            else
                zoomOut();
            setInteractive(true);
        }
        break;
    case Qt::ShiftModifier:
        if (!event->angleDelta().x()) {
            auto scrollBar = QAbstractScrollArea::horizontalScrollBar();

            scrollBar->setValue(scrollBar->value() - delta);
        }
        break;
    case Qt::NoModifier:
        if (!event->angleDelta().x()) {
            auto scrollBar = QAbstractScrollArea::verticalScrollBar();
            scrollBar->setValue(scrollBar->value() - delta);
        } else {
            //   QAbstractScrollArea::horizontalScrollBar()->setValue(QAbstractScrollArea::horizontalScrollBar()->value() - (event->delta()));
        }
        break;
    default:
        //QGraphicsView::wheelEvent(event);
        return;
    }
    //    mouseMove(mapToScene(pos));
    event->accept();
    update();
}

void GraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::MiddleButton) {
        setInteractive(false);
        // по нажатию средней кнопки мыши создаем событие ее отпускания выставляем моду перетаскивания и создаем событие зажатой левой кнопки мыши
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
        QMouseEvent releaseEvent(QEvent::MouseButtonRelease, event->localPos(), event->screenPos(), event->windowPos(), Qt::LeftButton, nullptr, event->modifiers());
#else
        QMouseEvent releaseEvent(QEvent::MouseButtonRelease, event->localPos(), event->screenPos(), event->windowPos(), Qt::LeftButton, event->buttons() | Qt::LeftButton, event->modifiers());
#endif
        QGraphicsView::mouseReleaseEvent(&releaseEvent);
        setDragMode(ScrollHandDrag);
        QMouseEvent fakeEvent(event->type(), event->localPos(), event->screenPos(), event->windowPos(), Qt::LeftButton, event->buttons() | Qt::LeftButton, event->modifiers());
        QGraphicsView::mousePressEvent(&fakeEvent);
    } else if (event->button() == Qt::RightButton) {

        // это что бы при вызове контекстного меню ничего постороннего не было
        setDragMode(NoDrag);
        setInteractive(false);

        QGraphicsView::mousePressEvent(event);
    } else {
        // это для выделения рамкой  - работа по-умолчанию левой кнопки мыши
        QGraphicsView::mousePressEvent(event);
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton) {
        // отпускаем левую кнопку мыши которую виртуально зажали в mousePressEvent
        QMouseEvent fakeEvent(event->type(), event->localPos(), event->screenPos(), event->windowPos(), Qt::LeftButton, event->buttons() & ~Qt::LeftButton, event->modifiers());
        QGraphicsView::mouseReleaseEvent(&fakeEvent);
        setDragMode(RubberBandDrag);
        setInteractive(true);
    } else if (event->button() == Qt::RightButton) {
        // это что бы при вызове контекстного меню ничего постороннего не было
        QGraphicsView::mousePressEvent(event);
        setDragMode(RubberBandDrag);
        setInteractive(true);

    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    //    auto item = scene()->itemAt(mapToScene(event->pos()), transform()); //itemAt(event->pos());
    //    if (item && item->type() == GiThermalPr) {
    //        if (item->flags() & QGraphicsItem::ItemIsSelectable)
    //            reinterpret_cast<ThermalPreviewItem*>(item)->node()->disable();
    //        else
    //            reinterpret_cast<ThermalPreviewItem*>(item)->node()->enable();
    //    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    //    vRuler->SetCursorPos(event->pos());
    //    hRuler->SetCursorPos(event->pos());
    //    const QPointF point(mappedPos(event));
    //    mouseMove(point);
    //    ShapePr::Constructor::updateShape(point);
    QGraphicsView::mouseMoveEvent(event);
}
