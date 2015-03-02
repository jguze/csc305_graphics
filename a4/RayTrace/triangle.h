#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <sceneobject.h>
#include <GL/gl.h>

/*
 * Broken and should not be used at this point in time
 */
class Triangle : public SceneObject
{
public:
    Triangle();
    void drawGeometry(QMatrix4x4 transform, SceneObjectProperties * sp);
    void intersects(Ray ray, QMatrix4x4 transform, HitRecord * hit);
    QVector3D getNormal(QVector3D p, QMatrix4x4 transform, HitRecord hit);

private:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> indices;
    std::vector<GLfloat> drawnVertices;


};

#endif // TRIANGLE_H
