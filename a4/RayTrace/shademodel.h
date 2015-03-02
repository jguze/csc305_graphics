#ifndef SHADEMODEL_H
#define SHADEMODEL_H

#include <QVector3D>
#include <lightsource.h>
#include <math.h>
#include <sceneobject.h>
#include <scenegraphnode.h>
#include <ray.h>

/*
 * The basic requirements for a shade model.
 */
class ShadeModel
{
public:
    ShadeModel();
    virtual ~ShadeModel() {}

    virtual QVector3D getPixelColour(SceneGraphNode * root, QVector3D cameraPos, SceneObjectProperties * sceneObjectProperties, double t,
                                     QVector3D surfaceNormal, QVector3D surfacePoint, std::vector<LightSource> lights, double currentRefractionIndex, QVector3D backgroundColour) = 0;
};

#endif // SHADEMODEL_H
