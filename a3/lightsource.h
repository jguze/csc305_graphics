#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <gl.h>
#include "linearalg.h"

class LightSource
{
public:
    LightSource() {}

    Vector4 ambient;
    Vector4 diffuse;
    Vector4 specular;
    QVector3D position;
    GLenum lightNumber;

};

#endif // LIGHTSOURCE_H
