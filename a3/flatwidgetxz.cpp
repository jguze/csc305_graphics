#include "flatwidgetxz.h"

FlatWidgetXZ::FlatWidgetXZ(DataManager * d) : FlatWidget(d)
{
}

QVector3D FlatWidgetXZ::get3DPoint(QVector2D point)
{
    return QVector3D(point.x(), 0, point.y());
}

QVector2D FlatWidgetXZ::get2DPoint(QVector3D point)
{
    return QVector2D(point.x(), point.z());
}

void FlatWidgetXZ::modifyPoint(QVector3D *point, QVector2D p)
{
    point->setX(p.x());
    point->setZ(p.y());
}
