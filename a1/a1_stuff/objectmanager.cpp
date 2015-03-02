#include "objectmanager.h"

ObjectManager::ObjectManager()
{
    screenPoints.reserve(MAXPOINTS);
    polygons.reserve(MAXPOLYGONS);
}

void ObjectManager::addPoint(Vector2 * point)
{
    screenPoints.push_back(point);
}

bool ObjectManager::canCreatePolygon(Vector2 * point)
{
    // Can't complete a polygon if there's only 2 points or less
    if (screenPoints.size() <= 2)
        return false;

    // Did the user click the first point
    if (onPoint(point, screenPoints.front(), (double)RADIUS))
    {
        return true;
    }
    return false;
}

// Iterate through all points on the screen, and then iterate through all points in each polygon to check for the point
Vector2 * ObjectManager::pointExists(Vector2 * point)
{
    polygonPoint = NULL;
    for (std::vector<Vector2 *>::iterator it = screenPoints.begin(); it != screenPoints.end(); it++)
    {
        if (onPoint(point, (*it), (double)RADIUS))
        {
            return (*it);
        }
    }
    for (std::vector<Polygon *>::iterator poly_it = polygons.begin(); poly_it != polygons.end(); poly_it++)
    {
        for (std::vector<Vector2 *>::iterator vector_it = (*poly_it)->points.begin(); vector_it != (*poly_it)->points.end(); vector_it++)
        {
            if (onPoint(point, (*vector_it), (double)RADIUS))
            {
                polygonPoint = *poly_it;
                return (*vector_it);
            }
        }
    }

    return NULL;
}

bool ObjectManager::onPoint(Vector2 * point, Vector2 * circle, double radius)
{
    return pow((point->x - circle->x), 2) + pow((point->y - circle->y), 2) <= pow(radius, 2);
}

// For each polygon, perform the raycast algorithm to check if the point lies in the polygon
Polygon * ObjectManager::polygonExists(Vector2 point)
{
    for (std::vector<Polygon *>::iterator it = polygons.begin(); it != polygons.end(); it++)
    {
        if (linalg::raycastAlgorithm(point, *(*it)))
        {
            return (*it);
        }
    }
    return NULL;
}
