#ifndef LAMBERTIANSHADEMODEL_H
#define LAMBERTIANSHADEMODEL_H

#include <shademodel.h>

// Very basic lambertian shading
class LambertianShadeModel : public ShadeModel
{
public:
    LambertianShadeModel();
    ~LambertianShadeModel() {}

    QVector3D getPixelColour(SceneGraphNode * root, QVector3D cameraPos, SceneObjectProperties * sceneObjectProperties, double t,
                             QVector3D surfaceNormal, QVector3D surfacePoint, std::vector<LightSource> lights, double currentRefractionIndex, QVector3D backgroundColour);
};

#endif // LAMBERTIANSHADEMODEL_H
