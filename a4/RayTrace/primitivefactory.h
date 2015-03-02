#ifndef PRIMITIVEFACTORY_H
#define PRIMITIVEFACTORY_H

#include <sceneobject.h>
#include <sphere.h>
#include <square.h>
#include <trianglemesh.h>
#include <cube.h>

#define PRIMITIVE_SIZE 4

/*
 * A factory pattern object to ensure we don't create multiple primitive objects for any object. This way, we
 * maintain only one sphere or one cube in the whole scene.
 */
class PrimitiveFactory
{
public:

    enum Primitive {
        SPHERE,
        FLAT_SQUARE,
        TRIANGLE_MESH,
        CUBE
    };

    PrimitiveFactory();

    // Gets the primitive as specified by the Primitive enum
    SceneObject * getSceneObject(Primitive p);
    int primitizeSize() {return PRIMITIVE_SIZE;}

private:
    static const QString PrimitiveStrings[PRIMITIVE_SIZE];
    std::vector<SceneObject *> sceneObjects;
};

#endif // PRIMITIVEFACTORY_H
