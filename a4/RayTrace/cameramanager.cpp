#include "cameramanager.h"

CameraManager::CameraManager()
{
}

QVector3D CameraManager::getCameraPos()
{
    if (depthPasses > 1)
    {
        return randomCameraPos;
    } else {
        return cameraPos;
    }
}

void CameraManager::randomizeCamera()
{
    QVector3D bl = cameraPos - ((lensWidth / 2) * u) - ((lensHeight / 2) * v);
    QVector3D tl = bl + lensHeight * v;
    QVector3D br = bl + lensWidth * u;
    double randU = (double)std::rand() / RAND_MAX;
    double randV = (double)std::rand() / RAND_MAX;
    randomCameraPos = cameraPos - (0.5 * u) - (0.5 * v) + (randU * u) + (randV * v);
    //randomCameraPos = bl + randomNumber * (tl - bl) + randomNumber * (br - bl);
}
