#include "ray.h"
#include <QDebug>
Ray::Ray()
{
}

void Ray::calculateUVW(QVector3D gaze, QVector3D up)
{
    w = (-gaze).normalized();
    u = QVector3D::crossProduct(up, w).normalized();
    v = QVector3D::crossProduct(w,u);
}

void Ray::calculateRay(double renderWidth, double renderHeight, double i, double j, QVector3D o, double focalLength)
{
    origin = o;
    double r = renderWidth / 2;
    double l = -r;
    double t = renderHeight / 2;
    double b = -t;
    double subu = l + (r - l) * (i + 0.5) / renderWidth;
    double subv = b + (t - b) * (j + 0.5) / renderHeight;
    direction = focalLength * -w + subu * u + subv * v;
}

QVector3D Ray::getPoint(double t)
{
    return origin + (t * direction);
}
