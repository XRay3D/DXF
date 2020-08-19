#pragma once



#include <QGraphicsView>

class GraphicsView final : public QGraphicsView {
    Q_OBJECT
    //Q_PROPERTY(double scale READ getScale WRITE setScale)
    const double zoomFactor = 1.5;

public:
    explicit GraphicsView(QWidget* parent = nullptr);
    ~GraphicsView() = default;
    double getScale();
    void zoomIn();
    void zoomOut();
signals:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};


