#include "primitivefactory.h"

PrimitiveFactory::PrimitiveFactory()
{
    sceneObjects.resize(PRIMITIVE_SIZE);
    sceneObjects[SPHERE] = new Sphere();
    sceneObjects[FLAT_SQUARE] = new Square();
    sceneObjects[TRIANGLE_MESH] = new TriangleMesh();
    sceneObjects[CUBE] = new Cube();
}

SceneObject * PrimitiveFactory::getSceneObject(Primitive p)
{
    return sceneObjects[p];
}

const QString PrimitiveFactory::PrimitiveStrings[PRIMITIVE_SIZE] = {
    "Sphere", "Square", "Triangle Mesh", "Cube"
};
