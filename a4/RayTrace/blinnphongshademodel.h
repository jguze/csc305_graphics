#ifndef BLINNPHONGSHADEMODEL_H
#define BLINNPHONGSHADEMODEL_H

#include <shademodel.h>

#define MAX_DEPTH 5

/*
 * More like the very robust shading model. It let's us do Blinn-Phong shading, as well as various other
 * forms of shading with shadows, reflection , and hopefully refraction
 */
class BlinnPhongShadeModel : public ShadeModel
{
public:

    BlinnPhongShadeModel();
    ~BlinnPhongShadeModel() {}

    // Gets the pixel colour given all the necessary information
    QVector3D getPixelColour(SceneGraphNode * root, QVector3D cameraPos, SceneObjectProperties * sceneObjectProperties, double t,
                             QVector3D surfaceNormal, QVector3D surfacePoint, std::vector<LightSource> lights, double currentRefractionIndex, QVector3D backgroundColour);

    // Determines if a point is in the shadow for a given light source
    bool isInShadow(SceneGraphNode * root, LightSource light, QVector3D surfacePoint);

private:

    // The pixel colour recursive call that adds in a level
    QVector3D getPixelColour(SceneGraphNode * root, QVector3D cameraPos, SceneObjectProperties * sceneObjectProperties, double t,
                             QVector3D surfaceNormal, QVector3D surfacePoint, std::vector<LightSource> lights, double currentRefractionIndex,
                             QVector3D backgroundColour, int level);

    // The functionality to properly apply reflection
    QVector3D idealSpecularReflection(SceneGraphNode * root, QVector3D cameraPos, QVector3D surfacePoint, SceneObjectProperties * sceneObjectProperties,
                                                            QVector3D surfaceNormal, std::vector<LightSource> lights, double currentRefractionIndex, QVector3D backgroundColour, int level);

    // Refraction. If it is total internal reflection, return false, else set newDirVec to the refraction vector
    bool refract(QVector3D normal, QVector3D * direction, double dn, double currentRefractionIndex, double nextRefractionIndex, QVector3D * newDirVec);

    // A basic function that will fire a new ray and return the colour
    QVector3D fireRay(Ray ray, SceneGraphNode * root, std::vector<LightSource> lights, double currentRefractionIndex, QVector3D backgroundColour, int level);

    // Computes the Schlick approximation for a value
    double schlickApprox(double dn, double n1, double n2);
};

#endif // BLINNPHONGSHADEMODEL_H
