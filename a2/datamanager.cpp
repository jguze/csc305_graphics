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

