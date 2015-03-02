#include "flatwidgetyz.h"

FlatWidgetYZ::FlatWidgetYZ(DataManager * d) : FlatWidget(d)
{
}

QVector3D FlatWidgetYZ::get3DPoint(QVector2D point)
{
    return QVector3D(0, point.x(), point.y());
}

QVector2D FlatWidgetYZ::get2DPoint(QVector3D point)
{
    return QVector2D(point.y(), point.z());
}

void FlatWidgetYZ::modifyPoint(QVector3D *point, QVector2D p)
{
    point->setY(p.x());
    point->setZ(p.y());
}
