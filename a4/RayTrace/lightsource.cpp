#include "lightsource.h"

LightSource::LightSource()
{
    intensity = 1;
    position = QVector3D(1,1,1);
    ambientIntensity = 0.2;
}

LightSource::LightSource(QVector3D _position, double _intensity, double _ambientIntensity, PrimitiveFactory * primitiveFactory)
{
    position = _position;
    intensity = _intensity;
    ambientIntensity = _ambientIntensity;
    sphere = primitiveFactory->getSceneObject(PrimitiveFactory::SPHERE);
}

QVector3D LightSource::getDirection(QVector3D surfacePoint)
{
    return (position - surfacePoint);
}

double LightSource::intersect(Ray ray)
{
    HitRecord hitRecord;
    hitRecord.t = double(1000.0);
    hitRecord.min_t = double(EPSILON);
    QMatrix4x4 transform;
    transform.translate(position);
//    transform = transform.inverted();
//    ray.origin = transform * ray.origin;
//    ray.direction = transform * ray.direction;
    sphere->intersects(ray, transform, &hitRecord);
    return hitRecord.t;
}


