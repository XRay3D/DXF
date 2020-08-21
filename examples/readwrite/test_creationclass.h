/**
 * @file test_creationclass.h
 */

/*****************************************************************************
**  $Id: test_creationclass.h 8865 2008-02-04 18:54:02Z andrew $
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

#ifndef TEST_CREATIONCLASS_H
#define TEST_CREATIONCLASS_H

#include "dl_creationadapter.h"
#include <QPolygonF>
/**
 * This class takes care of the entities read from the file.
 * Usually such a class would probably store the entities.
 * this one just prints some information about them to stdout.
 *
 * @author Andrew Mustun
 */

class Test_CreationClass final : public DL_CreationAdapter {
public:
    Test_CreationClass();
    ~Test_CreationClass() = default;

    void addLayer(const DL_LayerData& data) override;
    void addPoint(const DL_PointData& data) override;
    void addLine(const DL_LineData& data) override;
    void addArc(const DL_ArcData& data) override;
    void addCircle(const DL_CircleData& data) override;
    void addPolyline(const DL_PolylineData& data) override;
    void addVertex(const DL_VertexData& data) override;
    void add3dFace(const DL_3dFaceData& data) override;

    void printAttributes();
    QPolygonF polygon;
};

#endif
