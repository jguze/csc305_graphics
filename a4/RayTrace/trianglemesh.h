#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <sceneobject.h>
#include <GL/gl.h>
#include <QVector3D>

/*
 * A triangle mesh primitive. Will take in the set of vertices and indices, and
 * draw itself. It will also handle it's own intersection, which requires going through every
 * vertex in the mesh and comparing if it's valid. To speed up intersection, a bounding sphere with
 * a radius slightly larger than the farthest vertex in the mesh is created.
 */
class TriangleMesh : public SceneObject
{
public:
    TriangleMesh();
    void drawGeometry(QMatrix4x4 transform, SceneObjectProperties * sp);
    void intersects(Ray ray, QMatrix4x4 transform, HitRecord * hitRecord);
    QVector3D getNormal(QVector3D p, QMatrix4x4 transform, HitRecord hit);
    void completeGeometry(double maxLength);

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> drawnVertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
    std::vector<GLushort> normalIndices;
    SceneObject * boundingBox;
    QMatrix4x4 boundingBoxTransform;
    bool normalsSet;

private:
    void intersects(Ray ray, QVector3D vec_a, QVector3D vec_b, QVector3D vec_c, QMatrix4x4 transform, HitRecord * hit, int index);
};

#endif // TRIANGLEMESH_H
