#include "trianglemesh.h"

TriangleMesh::TriangleMesh()
{
    normalsSet = false;
    boundingBox = NULL;
}


void TriangleMesh::drawGeometry(QMatrix4x4 localTransform, SceneObjectProperties * sp)
{
    QVector3D a;
    QVector3D b;
    QVector3D c;
    int a_index;
    int b_index;
    int c_index;
    drawnVertices.clear();
    drawnVertices.resize(indices.size() * 3);
    for (unsigned int i = 0; i < indices.size(); i += 3)
    {
        a_index = indices[i] * 3;
        b_index = indices[i + 1] * 3;
        c_index = indices[i + 2] * 3;
        a = localTransform * QVector3D(vertices[a_index], vertices[a_index + 1], vertices[a_index + 2]);
        b = localTransform * QVector3D(vertices[b_index], vertices[b_index + 1], vertices[b_index + 2]);
        c = localTransform * QVector3D(vertices[c_index], vertices[c_index + 1], vertices[c_index + 2]);
        drawnVertices[a_index] = a.x();
        drawnVertices[a_index + 1] = a.y();
        drawnVertices[a_index + 2] = a.z();
        drawnVertices[b_index] = b.x();
        drawnVertices[b_index + 1] = b.y();
        drawnVertices[b_index + 2] = b.z();
        drawnVertices[c_index] = c.x();
        drawnVertices[c_index + 1] = c.y();
        drawnVertices[c_index + 2] = c.z();
    }

//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
    glColor3f(sp->colour.x(), sp->colour.y(), sp->colour.z());
    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &drawnVertices[0]);
//    if (normalsSet)
//    {
//        glNormalPointer(GL_FLOAT, 0, &normals[0]);
//    }
//    glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
//    glPopMatrix();
}

void TriangleMesh::intersects(Ray ray, QMatrix4x4 transform, HitRecord * hitRecord)
{
    if (boundingBox != NULL)
    {
        HitRecord tempHit;
        tempHit.hit = false;
        tempHit.min_t = hitRecord->min_t;
        tempHit.t = hitRecord->t;
        boundingBox->intersects(ray, boundingBoxTransform, &tempHit);
        if (!tempHit.hit)
        {
            return;
        }
    }

    QVector3D a;
    QVector3D b;
    QVector3D c;
    int a_index;
    int b_index;
    int c_index;
    for (unsigned int i = 0; i < indices.size(); i += 3)
    {
        a_index = indices[i] * 3;
        b_index = indices[i + 1] * 3;
        c_index = indices[i + 2] * 3;
        a = transform * QVector3D(vertices[a_index], vertices[a_index + 1], vertices[a_index + 2]);
        b = transform * QVector3D(vertices[b_index], vertices[b_index + 1], vertices[b_index + 2]);
        c = transform * QVector3D(vertices[c_index], vertices[c_index + 1], vertices[c_index + 2]);
        intersects(ray, a, b, c, transform, hitRecord, i);
    }
    return;
}

void TriangleMesh::intersects(Ray ray, QVector3D vec_a, QVector3D vec_b, QVector3D vec_c, QMatrix4x4 transform, HitRecord * hit, int index)
{
    double t, gamma, beta;
    double a = vec_a.x() - vec_b.x();
    double b = vec_a.y() - vec_b.y();
    double c = vec_a.z() - vec_b.z();
    double d = vec_a.x() - vec_c.x();
    double e = vec_a.y() - vec_c.y();
    double f = vec_a.z() - vec_c.z();
    double j = vec_a.x() - ray.origin.x();
    double k = vec_a.y() - ray.origin.y();
    double l = vec_a.z() - ray.origin.z();

    double ei_hf = (e * ray.direction.z()) -  (f * ray.direction.y());
    double gf_di = (f * ray.direction.x()) - (d * ray.direction.z());
    double dh_eg = (d * ray.direction.y()) - (e * ray.direction.x());

    double M = (a * ei_hf) + (b * gf_di) + (c * dh_eg);

    double ak_jb = (a * k) - (j * b);
    double jc_al = (j * c) - (a * l);
    double bl_kc = (b * l) - (k * c);

    t = - ((f * ak_jb) + (e * jc_al) + (d * bl_kc)) / M;

    if (t < hit->min_t || t > hit->t)
    {
        return;
    }

    gamma = ((ray.direction.z() * ak_jb) + (ray.direction.y() * jc_al) + (ray.direction.x() * bl_kc)) / M;

    if (gamma < 0 || gamma > 1)
    {
        return;
    }

    beta = ((j * ei_hf) + (k * gf_di) + (l * dh_eg)) / M;
    if (beta < 0 || beta > (1 - gamma))
    {
        return;
    }

    hit->t = t;
    hit->a = vec_a;
    hit->b = vec_b;
    hit->c = vec_c;
    hit->hit = true;
    if (normalsSet)
    {
        hit->index = index;
        hit->gamma = gamma;
        hit->beta = beta;
    }
    return;

}

QVector3D TriangleMesh::getNormal(QVector3D p, QMatrix4x4 transform, HitRecord hit)
{
    if (!normalsSet)
    {
        QVector3D a = transform * hit.a;
        QVector3D b = transform * hit.b;
        QVector3D c = transform * hit.c;
        QVector3D u = b - a;
        QVector3D v = c - a;
        return QVector3D::crossProduct(u, v).normalized();
    } else {
        int i = hit.index;
        QVector3D na(normals[normalIndices[i]], normals[normalIndices[i + 1]], normals[normalIndices[i + 2]]);
        QVector3D nb(normals[normalIndices[i + 3]], normals[normalIndices[i + 4]], normals[normalIndices[i + 5]]);
        QVector3D nc(normals[normalIndices[i + 6]], normals[normalIndices[i + 7]], normals[normalIndices[i + 8]]);
//        return ((hit.gamma * nc) + (hit.beta * na) + ((1 - hit.gamma - hit.beta) * nb)).normalized();
        return (na + nb + nc) / 3;
    }
}

void TriangleMesh::completeGeometry(double maxLength)
{
    boundingBoxTransform.scale(maxLength); //unit circle
}
