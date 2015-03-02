#include "sceneobject.h"

SceneObject::SceneObject()
{
}

SceneObjectProperties::SceneObjectProperties()
{
    colour = QVector3D(1.0, 1.0, 1.0);
    shininess = 100;
    specularCoef = QVector3D(0.5, 0.5, 0.5);
    ambientColour = QVector3D(0.5, 0.5, 0.5);
    refractionIndex = 0;
    mirror = 1;
}

bool SceneObjectProperties::isTransparent()
{
    if (refractionIndex == 0)
    {
        return false;
    } else {
        return true;
    }
}

HitRecord::HitRecord()
{
    hit = false;
}
