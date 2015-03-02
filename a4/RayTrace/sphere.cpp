#include "sphere.h"

/**
 * @brief The SolidSphere class Sphere code from datenwolf found on StackOverflow here:
 * http://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c
 */
Sphere::Sphere()
{
    float radius = 1;
    unsigned int rings = 12;
    unsigned int sectors = 24;
    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    unsigned int r, s;

    vertices.resize(rings * sectors * 3);
    drawnVertices.resize(rings * sectors * 3);
    normals.resize(rings * sectors * 3);
    texcoords.resize(rings * sectors * 2);
    std::vector<GLfloat>::iterator v = vertices.begin();
    std::vector<GLfloat>::iterator n = normals.begin();
    std::vector<GLfloat>::iterator t = texcoords.begin();
    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
            float const y = sin( -M_PI_2 + M_PI * r * R );
            float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
            float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

            *t++ = s*S;
            *t++ = r*R;

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;

            *n++ = x;
            *n++ = y;
            *n++ = z;
    }

    indices.resize(rings * sectors * 4);
    std::vector<GLushort>::iterator i = indices.begin();
    for(r = 0; r < rings-1; r++)
        for(s = 0; s < sectors-1; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
        }
}

void Sphere::drawGeometry(QMatrix4x4 localTransform, SceneObjectProperties * sp)
{
    for (unsigned int i = 0; i < vertices.size(); i += 3)
    {
        QVector3D v(vertices[i], vertices[i + 1], vertices[i + 2]);
        v = localTransform * v;
        drawnVertices[i] = v.x();
        drawnVertices[i + 1] = v.y();
        drawnVertices[i + 2] = v.z();
    }

//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
    glColor3f(sp->colour.x(), sp->colour.y(), sp->colour.z());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &drawnVertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normals[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
    glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
//    glPopMatrix();
}

void Sphere::intersects(Ray ray, QMatrix4x4 transform, HitRecord * hit)
{
    QVector3D origin(0,0,0);
    QVector3D arbPoint(vertices[0], vertices[1], vertices[2]);
    origin = transform * origin;
    arbPoint = transform * arbPoint;

    double radius = (origin - arbPoint).length();
    QVector3D subOrigins = ray.origin - origin;

    double A = QVector3D::dotProduct(ray.direction, ray.direction);
    double B = QVector3D::dotProduct( ray.direction, subOrigins);
    double C = QVector3D::dotProduct(subOrigins, subOrigins) - (radius * radius);
    double discriminant = (B * B) - (A * C);

    if (discriminant < EPSILON)
    {
        return;
    }

    double squareRoot = sqrt(discriminant);

    double t1 = (-B + squareRoot) / A;
    double t2 = (-B - squareRoot) / A;
    double t;
    if (t1 < t2)
    {
        t = t1;
    } else {
        t = t2;
    }

    if (t > hit->min_t && t < hit->t)
    {
        hit->t = t;
        hit->hit = true;
    }
    return;
}

QVector3D Sphere::getNormal(QVector3D p, QMatrix4x4 transform, HitRecord hit)
{
    QVector3D origin(0,0,0);
    origin = transform * origin;

    double radius = (p - origin).length();
    return (p - origin) / radius;
}

