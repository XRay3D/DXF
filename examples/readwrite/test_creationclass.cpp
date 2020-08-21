/*
 * @file test_creationclass.cpp
 */

/*****************************************************************************
**  $Id: test_creationclass.cpp 8865 2008-02-04 18:54:02Z andrew $
**
**  This is part of the dxflib library
**  Copyright (C) 2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#include "test_creationclass.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QPen>
#include <iostream>
#include <stdio.h>

extern QGraphicsScene* scene;

/**
 * Default constructor.
 */
Test_CreationClass::Test_CreationClass() { }

/**
 * Sample implementation of the method which handles layers.
 */
void Test_CreationClass::addLayer(const DL_LayerData& data)
{
    qDebug("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
    //printAttributes();
}

/**
 * Sample implementation of the method which handles point entities.
 */
void Test_CreationClass::addPoint(const DL_PointData& data)
{
    qDebug("POINT    (%6.3f, %6.3f, %6.3f)\n",
        data.x, data.y, data.z);
    //printAttributes();
}

/**
 * Sample implementation of the method which handles line entities.
 */
void Test_CreationClass::addLine(const DL_LineData& data)
{
    scene->addLine({ { data.x1, data.y1 }, { data.x2, data.y2 } },
        QPen(QColor(0, 0, 0, 100), 0.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    qDebug("LINE     (%6.3f, %6.3f, %6.3f) (%6.3f, %6.3f, %6.3f)\n",
        data.x1, data.y1, data.z1, data.x2, data.y2, data.z2);
    //printAttributes();
}

/**
 * Sample implementation of the method which handles arc entities.
 */
void Test_CreationClass::addArc(const DL_ArcData& data)
{
    qDebug("ARC      (%6.3f, %6.3f, %6.3f) %6.3f, %6.3f, %6.3f\n",
        data.cx, data.cy, data.cz,
        data.radius, data.angle1, data.angle2);
    //printAttributes();
}

/**
 * Sample implementation of the method which handles circle entities.
 */
void Test_CreationClass::addCircle(const DL_CircleData& data)
{
    QPointF с(data.cx, data.cy);
    QPointF r(data.radius, data.radius);
    scene->addEllipse(QRectF(с - r, с + r), QPen(QColor(0, 0, 0, 100), 0.0 /*thickness*/ /*, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin*/), Qt::NoBrush);

    qDebug("CIRCLE   (%6.3f, %6.3f, %6.3f) %6.3f\n",
        data.cx, data.cy, data.cz,
        data.radius);
    //printAttributes();
}

/**
 * Sample implementation of the method which handles polyline entities.
 */
void Test_CreationClass::addPolyline(const DL_PolylineData& data)
{
    if (!polygon.isEmpty())
        scene->addPolygon(polygon, QPen(QColor(0, 0, 0, 100), 0.0 /*width*/, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), Qt::NoBrush);
    polygon.clear();
    qDebug("POLYLINE \n");
    qDebug("flags: %d\n", (int)data.flags);
    printAttributes();
}

/**
 * Sample implementation of the method which handles vertices.
 */
void Test_CreationClass::addVertex(const DL_VertexData& data)
{
    polygon.append({ data.x, data.y });
    qDebug("VERTEX   (%6.3f, %6.3f, %6.3f) %6.3f\n",
        data.x, data.y, data.z,
        data.bulge);
    //printAttributes();
}

void Test_CreationClass::add3dFace(const DL_3dFaceData& data)
{
    qDebug("3DFACE\n");
    for (int i = 0; i < 4; i++) {
        qDebug("   corner %d: %6.3f %6.3f %6.3f\n",
            i, data.x[i], data.y[i], data.z[i]);
    }
    //printAttributes();
}

void Test_CreationClass::printAttributes()
{
    qDebug("  Attributes: Layer: %s, ", attributes.getLayer().c_str());
    qDebug(" Color: ");
    if (attributes.getColor() == 256) {
        qDebug("BYLAYER");
    } else if (attributes.getColor() == 0) {
        qDebug("BYBLOCK");
    } else {
        qDebug("%d", attributes.getColor());
    }
    qDebug(" Width: ");
    if (attributes.getWidth() == -1) {
        qDebug("BYLAYER");
    } else if (attributes.getWidth() == -2) {
        qDebug("BYBLOCK");
    } else if (attributes.getWidth() == -3) {
        qDebug("DEFAULT");
    } else {
        qDebug("%d", attributes.getWidth());
    }
    qDebug(" Type: %s\n", attributes.getLinetype().c_str());
}

// EOF
