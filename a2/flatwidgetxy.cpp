#include "flatwidgetxy.h"

FlatWidgetXY::FlatWidgetXY(DataManager * d) : FlatWidget(d)
{
}

QVector3D FlatWidgetXY::get3DPoint(QVector2D point)
{
    return QVector3D(point.x(), point.y(), 0);
}

QVector2D FlatWidgetXY::get2DPoint(QVector3D point)
{
    return QVector2D(point.x(), point.y());
}

void FlatWidgetXY::modifyPoint(QVector3D *point, QVector2D p)
{
    point->setX(p.x());
    point->setY(p.y());
}
