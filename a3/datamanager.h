#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVector3D>
#include <QVector>
#include <QDebug>
#include "linearalg.h"
#include "lightsource.h"
#include "common.h"

#define SAMPLE_STEP 0.05
/**
 * @brief The DataManager class A class that contains all points in the system,
 * and methods to manipulate the points, or get the catmull-rom spline
 */
class DataManager
{
public:
    /**
     * @brief DataManager Empty constructor for the DataManager
     */
    DataManager();

    /**
     * @brief points All the points in the system in 3D coordinates
     */
    QVector<QVector3D *> points;

    /**
     * @brief addPoint Adds a 3D point to the points vector
     * @param point A 3D point to be added to the display
     */
    void addPoint(QVector3D * point);

    /**
     * @brief calculateCatmullRom Calculates the catmull-rom spline given the current
     * set of points in the system. This method returns an empty list of Vector3 points
     * if there are less than 4 points in the system. This returns a set of points that
     * represent a spline curve given the points in the system.
     * @return An empty list if there are less than 4 points in the system, otherwise a list
     * of 3D points representing the catmull-rom spline
     */
    QVector<Vector3> calculateCatmullRom();

    struct f_frame calculateFrame(Shape shape, double radius);

    int closestPointIndex(int a, Polygon3 prevPolygon, Polygon3 curPolygon);

    QVector<LightSource> lights;

    /**
     * @brief catmullRom The CatmullRom object from the linear algebra library to calculate the catmull-rom spline
     */
    CatmullRom catmullRom;
};

#endif // DATAMANAGER_H
