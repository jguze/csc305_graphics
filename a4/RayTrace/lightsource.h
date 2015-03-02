#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QVector3D>
#include <primitivefactory.h>
#include <ray.h>
#include <QMatrix4x4>

/*
 * A basic point light source. Comes with a position, intensity, and a shape defined as a sphere.
 */
class LightSource
{
public:
    LightSource();
    LightSource(QVector3D _position, double _intensity, double _ambientIntensity, PrimitiveFactory * primitiveFactory);
    QVector3D position;
    double intensity;
    double ambientIntensity;
    SceneObject * sphere;

    QVector3D getDirection(QVector3D surfacePoint);
    double intersect(Ray ray);

};



#endif // LIGHTSOURCE_H
