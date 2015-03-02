#include "lambertianshademodel.h"

LambertianShadeModel::LambertianShadeModel()
{
}

QVector3D LambertianShadeModel::getPixelColour(SceneGraphNode * root, QVector3D cameraPos, SceneObjectProperties * sceneObjectProperties, double t,
                                                QVector3D surfaceNormal, QVector3D surfacePoint, std::vector<LightSource> lights, double currentRefractionIndex, QVector3D backgroundColour)
{
    QVector3D pixelColour(0,0,0);
    for (std::vector<LightSource>::iterator it = lights.begin(); it != lights.end(); it++ )
    {
        pixelColour += sceneObjectProperties->colour * it->intensity * fmax(QVector3D::dotProduct(it->getDirection(surfacePoint).normalized(), surfaceNormal), 0);
    }
    pixelColour = QVector3D(fmin(pixelColour.x(), 1), fmin(pixelColour.y(), 1), fmin(pixelColour.z(), 1));
    return  pixelColour;
}
