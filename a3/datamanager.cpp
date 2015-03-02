#include "datamanager.h"

DataManager::DataManager()
{
}

void DataManager::addPoint(QVector3D *point)
{
    points.push_front(point);
    calculateCatmullRom();
}


QVector<Vector3> DataManager::calculateCatmullRom()
{
    QVector<Vector3> catmullList;
    Vector3 catmullVector;
    for (int i = 0; i < points.size() - 3; i++)
    {
        for (double j = 0; j < 1; j += SAMPLE_STEP)
        {
            catmullVector = catmullRom.calcSpline(j, Vector3(*(points[i])), Vector3(*(points[i + 1])), Vector3(*(points[i + 2])), Vector3(*(points[i + 3])));
            catmullList.append(catmullVector);
        }
    }
    return catmullList;
}

struct f_frame DataManager::calculateFrame(Shape shape, double radius)
{
    QVector<Polygon3> surfacePointList;
    QVector<FrenetCrossSection> crossSectionList;
    FrenetCrossSection * crossSection;
    Matrix44 * rotationMatrix;
    Vector2 * cValue = new Vector2(radius,radius);
    QVector<Vector3> list;
    double angle;
    struct f_frame f;
    f.noValue = true;

//    if (points.size() < 4)
//    {
//        return f;
//    }

    switch(shape)
    {
        case CIRCLE:
            angle = 15;
            break;
        case SQUARE:
            angle = 90;
            break;
        case SPECIAL:
            angle = 15;
            break;
        default:
            angle = 15;
            break;
    }

    for (int i = 0; i < points.size() - 3; i++)
    {
        for (double j = 0; j < 1; j += SAMPLE_STEP)
        {
            crossSection = catmullRom.calcFrame(j, Vector3(*(points[i])), Vector3(*(points[i + 1])), Vector3(*(points[i + 2])), Vector3(*(points[i + 3])), radius);
            crossSection->surfacePoint.splinePoint = Vector3temp(crossSection->curvePoint.x, crossSection->curvePoint.y, crossSection->curvePoint.z);
            list.append(crossSection->surfacePoint);
            if (shape == SPECIAL)
            {
                rotationMatrix = linalg::rotateLineUVW(crossSection->curvePoint, crossSection->tangent, angle);
            }
            for (int k = 0; k < 360 / angle; k++)
            {
                if (shape != SPECIAL)
                {
                    *cValue = *linalg::rotate2(angle) * *cValue;
                    crossSection->setC(*cValue);
                } else {
                    crossSection->surfacePoint = *rotationMatrix * crossSection->surfacePoint;
                }
                crossSection->surfacePoint.splinePoint = Vector3temp(crossSection->curvePoint.x, crossSection->curvePoint.y, crossSection->curvePoint.z);
                list.append(crossSection->surfacePoint);
            }
            crossSectionList.push_back(*crossSection);
            surfacePointList.append(Polygon3(list));
            list.clear();
        }
    }

    //Create the triangles of the tube
    Vector3 prev0, prev1, p0, p1;
    Polygon3 prevPolygon;
    QVector<Triangle3> triangles;
    bool firstPoint = true;
    int closestIndex;
    for (QVector<Polygon3>::iterator pit = surfacePointList.begin(); pit != surfacePointList.end(); pit++)
    {
        if (firstPoint)
        {
            firstPoint = false;
        } else {
            switch(shape)
            {
                case CIRCLE:
                    closestIndex = closestPointIndex(0, prevPolygon, *pit);
                    for (int i = 0; i < pit->points.size(); i++)
                    {
                        prev0 = prevPolygon.points[i];
                        prev1 = prevPolygon.points[(i + 1) % pit->points.size()];
                        p0 = pit->points[(i + closestIndex) % pit->points.size()];
                        p1 = pit->points[(i + 1 + closestIndex) % pit->points.size()];
                        triangles.append(Triangle3(prev0, p0, prev1));
                        triangles.append(Triangle3(p0, p1, prev1));
                    }
                    break;

            case SPECIAL:
                closestIndex = closestPointIndex(0, prevPolygon, *pit);
                for (int i = 0; i < pit->points.size(); i++)
                {
                    prev0 = prevPolygon.points[i];
                    prev1 = prevPolygon.points[(i + 1) % pit->points.size()];
                    p0 = pit->points[(i + closestIndex) % pit->points.size()];
                    p1 = pit->points[(i + 1 + closestIndex) % pit->points.size()];
                    triangles.append(Triangle3(prev0, p0, prev1));
                    triangles.append(Triangle3(p0, p1, prev1));
                }
                break;
            default:
                for (int i = 0; i < pit->points.size(); i++)
                {
                    closestIndex = closestPointIndex(i, prevPolygon, *pit);
                    prev0 = prevPolygon.points[i];
                    prev1 = prevPolygon.points[(i + 1) % pit->points.size()];
                    p0 = pit->points[(closestIndex) % pit->points.size()];
                    p1 = pit->points[(closestIndex + 1) % pit->points.size()];
                    triangles.append(Triangle3(prev0, p0, prev1));
                    triangles.append(Triangle3(p0, p1, prev1));
                }
            }
        }
        prevPolygon = *pit;
    }

    QVector<Triangle3> lids;
    if (surfacePointList.size() > 0)
    {
        Polygon3 first = surfacePointList.first();
        Vector3 first_center = crossSectionList.first().curvePoint;
        Vector3 last_center = crossSectionList.last().curvePoint;
        Polygon3 last = surfacePointList.last();
        for (int i = 0; i < first.points.size(); i++)
        {
            lids.append(Triangle3(first.points[i], first.points[(i + 1) % first.points.size()], first_center));
            lids.append(Triangle3(last.points[i], last.points[(i + 1) % first.points.size()], last_center));
        }
    }
    f.crossSectionList = crossSectionList;
    f.cylinderList = triangles;
    f.lids = lids;
    f.noValue = false;
    return f;
}

int DataManager::closestPointIndex(int a, Polygon3 prevPolygon, Polygon3 curPolygon)
{
    double closestDistance;
    double tempDistance;
    int closestIndex = a;
    closestDistance = linalg::distance(prevPolygon.points[a], curPolygon.points[a]);
    for (int i = 1; i < curPolygon.points.size(); i++)
    {
        tempDistance = linalg::distance(prevPolygon.points[a], curPolygon.points[(i + a) % curPolygon.points.size()]);
        if (tempDistance < closestDistance)
        {
            closestDistance = tempDistance;
            closestIndex = i;
        }
    }
    return closestIndex;
}

