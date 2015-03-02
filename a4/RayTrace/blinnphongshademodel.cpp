#include "blinnphongshademodel.h"

BlinnPhongShadeModel::BlinnPhongShadeModel()
{
}


QVector3D BlinnPhongShadeModel::getPixelColour(SceneGraphNode * root, QVector3D cameraPos, SceneObjectProperties * sceneObjectProperties, double t,
                                                QVector3D surfaceNormal, QVector3D surfacePoint, std::vector<LightSource> lights,double currentRefractionIndex, QVector3D backgroundColour)
{
    return getPixelColour(root, cameraPos, sceneObjectProperties, t, surfaceNormal, surfacePoint, lights, currentRefractionIndex, backgroundColour, 1);
}



QVector3D BlinnPhongShadeModel::getPixelColour(SceneGraphNode * root, QVector3D cameraPos, SceneObjectProperties * sceneObjectProperties, double t,
                                                QVector3D surfaceNormal, QVector3D surfacePoint, std::vector<LightSource> lights, double currentRefractionIndex, QVector3D backgroundColour, int level)
{
    if (level > MAX_DEPTH)
    {
        return QVector3D(0,0,0);
    }

    QVector3D lightDir;
    QVector3D h;
    double maxnh;
    double maxnl;
    QVector3D v = (cameraPos - surfacePoint).normalized();
//    QVector3D v = (surfacePoint - cameraPos);

    QVector3D ambient = sceneObjectProperties->ambientColour * lights[0].ambientIntensity;
    QVector3D diffuse(0,0,0);
    QVector3D specular(0,0,0);
    QVector3D pixelColour(0,0,0);

    QVector3D refracted(0,0,0);
    double r = 1;
    double rCompl = 1;
    double g = 1;

    // Refraction and transparency
    while (sceneObjectProperties->isTransparent())
    {
        QVector3D refractedDir;
        double dn = QVector3D::dotProduct(v, surfaceNormal);
        double rIndex;
        if (dn < 0) //entering
        {
            refract(surfaceNormal, &v, dn, currentRefractionIndex, sceneObjectProperties->refractionIndex, &refractedDir);
            rIndex = currentRefractionIndex;
            r = schlickApprox(QVector3D::dotProduct(-v, surfaceNormal), currentRefractionIndex, sceneObjectProperties->refractionIndex);
        } else {
            //exiting
            if(refract(-surfaceNormal, &v, QVector3D::dotProduct(v, -surfaceNormal), 1, currentRefractionIndex, &refractedDir))
            {
                rIndex = 1;
                dn = QVector3D::dotProduct(refractedDir, surfaceNormal);
                r = schlickApprox(dn, 1.01, currentRefractionIndex);
            } else {
                break;
            }
        }
        g = 0.2;
        Ray ray;
        ray.origin = surfacePoint;
        ray.direction = refractedDir;
        refracted = fireRay(ray, root, lights, rIndex, backgroundColour, level + 1);
        rCompl = 1 - r;
        break; // MAKE THIS A FUNCTION LAZY
    }

    for (std::vector<LightSource>::iterator it = lights.begin(); it != lights.end(); it++)
    {
        if (!isInShadow(root, *it, surfacePoint))
        {
            lightDir = it->getDirection(surfacePoint).normalized();
            h = (lightDir - v).normalized();
            maxnh = fmax(QVector3D::dotProduct(h, surfaceNormal), 0);
            maxnl = fmax(QVector3D::dotProduct(surfaceNormal, lightDir), 0);

            diffuse += (sceneObjectProperties->colour * it->intensity * maxnl);
            if (sceneObjectProperties->mirror != 0)
            {
                specular += (sceneObjectProperties->specularCoef * it->intensity * (pow(maxnh, sceneObjectProperties->shininess)));
            }
        }
    }

    pixelColour += ambient + diffuse + specular;
    QVector3D reflected(0,0,0);
    reflected = idealSpecularReflection(root, cameraPos, surfacePoint, sceneObjectProperties, surfaceNormal, lights, currentRefractionIndex, backgroundColour, level);
    pixelColour = (g * pixelColour) + (r * reflected) + (rCompl * refracted);

    pixelColour = QVector3D(fmin(pixelColour.x(), 1), fmin(pixelColour.y(), 1), fmin(pixelColour.z(), 1));
    return pixelColour;
}

QVector3D BlinnPhongShadeModel::idealSpecularReflection(SceneGraphNode * root, QVector3D cameraPos, QVector3D surfacePoint, SceneObjectProperties * sceneObjectProperties,
                                                        QVector3D surfaceNormal, std::vector<LightSource> lights, double currentRefractionIndex, QVector3D backgroundColour, int level)
{
    //Reflection model
    QVector3D pixelColour(0,0,0);
    QVector3D d = (surfacePoint - cameraPos).normalized();
    QVector3D r = (d - 2 * (QVector3D::dotProduct(d, surfaceNormal) * surfaceNormal));
    Ray ray;
    ray.origin = surfacePoint;
    ray.direction = r;

    pixelColour += (sceneObjectProperties->specularCoef * fireRay(ray, root, lights, currentRefractionIndex, backgroundColour, level + 1));
    return pixelColour;
}

bool BlinnPhongShadeModel::isInShadow(SceneGraphNode *root, LightSource light, QVector3D surfacePoint)
{
    Ray shadowRay;
    shadowRay.origin = surfacePoint;
    shadowRay.direction = light.getDirection(surfacePoint).normalized();
    double min_t = double(EPSILON);
    double max_t = double(light.intersect(shadowRay));

    HitRecord hitRecord = root->queryScene(shadowRay, &min_t, &max_t);
    return hitRecord.hit;
}

bool BlinnPhongShadeModel::refract(QVector3D normal, QVector3D *direction, double dn, double currentRefractionIndex, double nextRefractionIndex, QVector3D * newDirVec)
{
    double irTerm = (pow(currentRefractionIndex, 2) / pow(nextRefractionIndex, 2)) * (1 - pow(dn, 2));
    irTerm = 1 - irTerm;
    if (irTerm < 0)
    {
        return false;
    }

    *newDirVec = (((currentRefractionIndex / nextRefractionIndex) * ( (*direction) - ( (normal) * dn) ) ) - ((normal) * sqrt(irTerm)));
    return true;
}

QVector3D BlinnPhongShadeModel::fireRay(Ray ray, SceneGraphNode * root, std::vector<LightSource> lights, double currentRefractionIndex, QVector3D backgroundColour, int level)
{
    QVector3D pixelColour(0,0,0);
    HitRecord hitRecord;
    double min_t = double(EPSILON);
    double max_t = double(1000.0);

    hitRecord = root->queryScene(ray, &min_t, &max_t);
    if (hitRecord.hit)
    {
        QVector3D p = ray.getPoint(hitRecord.t);
        pixelColour = getPixelColour(root, ray.origin, hitRecord.sceneObjectProperties, hitRecord.t, hitRecord.sceneObject->getNormal(p, hitRecord.transform, hitRecord),
                       p, lights, currentRefractionIndex, backgroundColour, level + 1);
    } else {
      pixelColour = backgroundColour;
    }
    pixelColour = QVector3D(fmin(pixelColour.x(), 1), fmin(pixelColour.y(), 1), fmin(pixelColour.z(), 1));
    return pixelColour;
}

double BlinnPhongShadeModel::schlickApprox(double dn, double n1, double n2)
{
    double r0 = pow(n1 - 1, 2) / pow(n1 + 1, 2);
    return r0 + (1 - r0) * pow(1 - dn, 5);
}
