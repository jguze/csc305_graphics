#include "triangle.h"

Triangle::Triangle()
{
    vertices.resize(9);
    drawnVertices.resize(9);

    vertices[0] = 0;
    vertices[1] = 0;
    vertices[2] = 0;

    vertices[3] = 1;
    vertices[4] = 0;
    vertices[5] = 0;

    vertices[6] = 0;
    vertices[7] = 0;
    vertices[8] = 1;
}

void Triangle::drawGeometry(QMatrix4x4 transform, SceneObjectProperties *sp)
{
    for (unsigned int i = 0; i < vertices.size(); i += 3)
    {
        QVector3D v(vertices[i], vertices[i + 1], vertices[i + 2]);
        v = transform * v;
        drawnVertices[i] = v.x();
        drawnVertices[i + 1] = v.y();
        drawnVertices[i + 2] = v.z();
    }

    glColor3f(sp->colour.x(), sp->colour.y(), sp->colour.z());
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &drawnVertices[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}

void Triangle::intersects(Ray ray, QMatrix4x4 transform, HitRecord * hit)
{

}

QVector3D Triangle::getNormal(QVector3D p, QMatrix4x4 transform, HitRecord hit)
{

}
