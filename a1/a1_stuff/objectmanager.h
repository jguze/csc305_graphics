#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include "linearalg.h"
#include "constants.h"

#define MAXPOINTS 50
#define MAXPOLYGONS 50


/**
 * @brief The ObjectManager class. It holds all objects on the screen, and limits access and modification to these objects
 */
class ObjectManager
{
public:
    /**
     * @brief ObjectManager The constructor for the class
     */
    ObjectManager();

    /**
     * @brief screenPoints A vector of points that are on the screen and not yet a polygon. A polygon has connected all it's points together.
     *      The screen points are simply points not fully connected yet
     */
    std::vector<Vector2 *> screenPoints;

    /**
     * @brief polygons A vector of Polygons, represented as a vector of points.
     */
    std::vector<Polygon *> polygons;

    /**
     * @brief addPoint Adds a point to the screenPoints vector
     * @param point The point to add to our list
     */
    void addPoint(Vector2 * point);

    /**
     * @brief canCreatePolygon Determines if a polygon can be created, which is determined if the point
     *      being chosen is the first point in the list of screenPoints.
     * @param point The point being determined if on the first point in screenPoints
     * @return True if the polygon can be created, false otherwise
     */
    bool canCreatePolygon(Vector2 * point);

    /**
     * @brief onPoint Checks if a point lies on a circle. The circle is represented by a Vector2 object, and its radius
     * @param point The point to determine if it lies on a circle
     * @param circle The x and y values of the circle
     * @param radius The radius of the circle
     * @return True if the point lies in the circle, false otherwise
     */
    bool onPoint(Vector2 * point, Vector2 * circle, double radius);

    /**
     * @brief pointExists Determines if a point exists at the coordinates of 'point'
     * @param point The x and y value to determine if a point exists at
     * @return A pointer to the Vector2 representing the point, NULL otherwise
     */
    Vector2 * pointExists(Vector2 * point);

    /**
     * @brief polygonExists Determine if a polygon exists at the coordinates of 'point'
     * @param point The point to check if a polygon exists at
     * @return A pointer to the Polygon if it exists, NULL otherwise
     */
    Polygon * polygonExists(Vector2 point);
    Polygon * polygonPoint;
};

#endif // OBJECTMANAGER_H
