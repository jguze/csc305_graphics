#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QMatrix4x4>
#include <ray.h>

#define EPSILON 0.001f

class SceneObjectProperties;
class HitRecord;

/*
 * The primitive for any object in the scene. Allows users to draw the current object using
 * a given transform, or get the normal for a point given the transform.
 */
class SceneObject
{
public:
    SceneObject();

    virtual void drawGeometry(QMatrix4x4 transform, SceneObjectProperties * sp) = 0;
    virtual void intersects(Ray ray, QMatrix4x4 transform, HitRecord * hitRecord) = 0;
    virtual QVector3D getNormal(QVector3D p, QMatrix4x4 transform, HitRecord hit) = 0;
};

/*
 * The material properties of an object
 */
class SceneObjectProperties
{
public:
    SceneObjectProperties();
    SceneObjectProperties(QVector3D _colour, double _shine, QVector3D _specCoef, QVector3D _ambientColour) :
        colour(_colour), shininess(_shine), specularCoef(_specCoef), ambientColour(_ambientColour) {refractionIndex = 0; mirror = 1;}
    SceneObjectProperties(QVector3D _colour, double _shine, QVector3D _specCoef, QVector3D _ambientColour, double _refractionIndex) :
        colour(_colour), shininess(_shine), specularCoef(_specCoef), ambientColour(_ambientColour), refractionIndex(_refractionIndex) {mirror = 1;}
    bool isTransparent();
    QVector3D colour;
    double shininess;
    QVector3D specularCoef;
    QVector3D ambientColour;
    double refractionIndex;
    double mirror;
};


class HitRecord
{
public:
    HitRecord();
    HitRecord(bool _hit) : hit(_hit) {}
    HitRecord(bool _hit, double _t) : hit(_hit), t(_t) {}

    bool hit;
    double t;
    SceneObjectProperties * sceneObjectProperties;
    QMatrix4x4 transform;
    SceneObject * sceneObject;
    QVector3D normal;
    QVector3D a;
    QVector3D b;
    QVector3D c;
    int index;
    double beta;
    double gamma;
    double min_t;
};

#endif // SCENEOBJECT_H
