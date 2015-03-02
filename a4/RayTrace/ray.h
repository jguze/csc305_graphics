#ifndef RAY_H
#define RAY_H

#include <QVector3D>

/*
 * A ray in the mathematical sense. Stores the UVW of the camera, as well as calculates the ray's direction and
 * origin based on the size of the image, the pixel position, and a focal length.
 */
class Ray
{
public:
    Ray();

    void calculateUVW(QVector3D gaze, QVector3D up);
    void calculateRay(double renderWidth, double renderHeight, double i, double j, QVector3D o, double focalLength);
    QVector3D getPoint(double t);

    QVector3D origin;
    QVector3D direction;
    QVector3D u;
    QVector3D v;
    QVector3D w;
};

#endif // RAY_H
