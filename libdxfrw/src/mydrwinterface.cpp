#include "mydrwinterface.h"
#include <QDebug>

MyDRWInterface::MyDRWInterface() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addHeader(const DRW_Header* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addLType(const DRW_LType& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addLayer(const DRW_Layer& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addDimStyle(const DRW_Dimstyle& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addVport(const DRW_Vport& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addTextStyle(const DRW_Textstyle& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addAppId(const DRW_AppId& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addBlock(const DRW_Block& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::setBlock(const int handle) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::endBlock() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addPoint(const DRW_Point& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addLine(const DRW_Line& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addRay(const DRW_Ray& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addXline(const DRW_Xline& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addArc(const DRW_Arc& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addCircle(const DRW_Circle& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addEllipse(const DRW_Ellipse& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addLWPolyline(const DRW_LWPolyline& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addPolyline(const DRW_Polyline& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addSpline(const DRW_Spline* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addKnot(const DRW_Entity& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addInsert(const DRW_Insert& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addTrace(const DRW_Trace& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::add3dFace(const DRW_3Dface& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addSolid(const DRW_Solid& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addMText(const DRW_MText& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addText(const DRW_Text& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addDimAlign(const DRW_DimAligned* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addDimLinear(const DRW_DimLinear* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addDimRadial(const DRW_DimRadial* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addDimDiametric(const DRW_DimDiametric* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addDimAngular(const DRW_DimAngular* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addDimAngular3P(const DRW_DimAngular3p* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addDimOrdinate(const DRW_DimOrdinate* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addLeader(const DRW_Leader* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addHatch(const DRW_Hatch* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addViewport(const DRW_Viewport& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addImage(const DRW_Image* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::linkImage(const DRW_ImageDef* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addComment(const char* comment) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::addPlotSettings(const DRW_PlotSettings* data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeHeader(DRW_Header& data) { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeBlocks() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeBlockRecords() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeEntities() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeLTypes() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeLayers() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeTextstyles() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeVports() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeDimstyles() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeObjects() { qDebug(Q_FUNC_INFO); }

void MyDRWInterface::writeAppId() { qDebug(Q_FUNC_INFO); }
