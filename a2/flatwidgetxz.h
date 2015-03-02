#ifndef FLATWIDGETXZ_H
#define FLATWIDGETXZ_H

#include "flatwidget.h"

/**
 * @brief The FlatWidgetXZ class A child of the FlatWidget class. It represents the XZ plane of the
 * 3D points
 */
class FlatWidgetXZ : public FlatWidget
{
    Q_OBJECT
public:
    /**
     * @brief FlatWidgetXZ Constructor that takes in the dataManager for the 3D points
     * @param d
     */
    FlatWidgetXZ(DataManager * d);
protected:
    /**
     * @brief get3DPoint Takes in a 3D xz point from this plane, and returns the 3D version of the point
     * @param point The 2D xy point from the plane
     * @return A 3D point where the Y value is 0
     */
    QVector3D get3DPoint(QVector2D point);

    /**
     * @brief get2DPoint Takes in a 3D point, and returns the 2D point for this xz plane
     * @param point The 3D point to translate to 2D xz
     * @return A 2D point where the x and y value is the x and z value of the 3D point
     */
    QVector2D get2DPoint(QVector3D point);

    /**
     * @brief modifyPoint Takes in a reference to a 3D point, and a 2D point from the xz plane, and
     * moves the 3D point to that point p without changing the y value
     * @param point A reference to the 3D point
     * @param p The point to move it to
     */
    void modifyPoint(QVector3D * point, QVector2D p);
};

#endif // FLATWIDGETXZ_H
