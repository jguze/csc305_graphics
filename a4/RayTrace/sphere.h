#ifndef SPHERE_H
#define SPHERE_H

#include <sceneobject.h>
#include <GL/gl.h>
#include <vector>
#include <QVector3D>
#include <QMatrix4x4>
#include <math.h>
#include <ray.h>

/*
 * A sphere primitive along with the appropriate draw, intersect, and normal functions
 */
class Sphere : public SceneObject
{
public:
    Sphere();
    void drawGeometry(QMatrix4x4 transform, SceneObjectProperties * sp);
    void intersects(Ray ray, QMatrix4x4 transform, HitRecord * hitRecord);
    QVector3D getNormal(QVector3D p, QMatrix4x4 transform, HitRecord hitRecord);

protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> drawnVertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
};

#endif // SPHERE_H
