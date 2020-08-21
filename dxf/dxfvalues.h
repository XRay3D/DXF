#pragma once
#include <QColor>

class Color : public QColor {
public:
    Color(double r, double g, double b)
        : QColor(r * 255, g * 255, b * 255)
    {
    }
};

extern const Color dxfColors[];
