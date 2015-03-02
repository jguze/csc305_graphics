#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QThread>

/*
 * TODO: Move raytrace code from the OpenGL widget to here. Makes it easier to launch threads later
 */
class RayTracer : public QThread
{
public:
    RayTracer();
};

#endif // RAYTRACER_H
