#ifndef FLATWIDGETYZ_H
#define FLATWIDGETYZ_H

#include "flatwidget.h"

/**
 * @brief The FlatWidgetYZ class A child of the FlatWidget class. It represents the YZ plane of the
 * 3D points
 */
class FlatWidgetYZ : public FlatWidget
{
    Q_OBJECT
public:
    /**
     * @brief FlatWidgetYZ Constructor that takes in the dataManager for the 3D points
     * @param d
     */
    FlatWidgetYZ(DataManager * d);
protected:
    /**
     * @brief get3DPoint Takes in a 2D point, and returns the 3D version of the point
     * @param point The 2D yz point from the plane
     * @return A 3D point where the X value is 0
     */
    QVector3D get3DPoint(QVector2D point);

    /**
     * @brief get2DPoint Takes in a 3D point, and reurns a 2D point for this yz plane
     * @param point The 3D point to translate to 2D yz
     * @return A 2D point where the x and y value are the y and z values of the 3D point
     */
    QVector2D get2DPoint(QVector3D point);

    /**
     * @brief modifyPoint Takes in a reference to a 3D point, and a 2D point from the yz plane, and
     * moves the 3D point to that point p without changing the x value.
     * @param point A reference to the 3D point
     * @param p The poont to move it to
     */
    void modifyPoint(QVector3D * point, QVector2D p);
};

#endif // FLATWIDGETYZ_H
