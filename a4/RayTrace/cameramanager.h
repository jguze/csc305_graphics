#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QVector3D>

/*
 * Basic camera fuctions and data, along with code to hopefully get depth of field in at the end
 */
class CameraManager
{
public:
    CameraManager();

    int depthPasses; // 1 is a normal camera
    QVector3D bottomLeft;
    QVector3D topLeft;
    QVector3D bottomRight;
    QVector3D cameraPos;
    QVector3D randomCameraPos;
    QVector3D viewTo;
    double lensWidth;
    double lensHeight;
    double focalLength;
    QVector3D u;
    QVector3D v;
    QVector3D w;

    void setUVW(QVector3D _u, QVector3D _v, QVector3D _w) {u = _u; v = _v; w = _w;}
    QVector3D getCameraPos();
    void randomizeCamera();

};

#endif // CAMERAMANAGER_H
