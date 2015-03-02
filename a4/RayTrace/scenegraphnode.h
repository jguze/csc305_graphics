#ifndef SCENEGRAPHNODE_H
#define SCENEGRAPHNODE_H

#include <QMatrix4x4>
#include <sceneobject.h>
#include <ray.h>
#include <QMatrix3x3>

/*
 * The core of the scene graph. Every node has a reference to
 * a current transform and a set of children, and every transform
 * affects it's children. Only the root node can be
 * modified at the top level. Every node but the root has a
 * primitive if needed, and a set of material properties. This
 * graph also allows for travering to look for a hit fairly straightforward
 */
class SceneGraphNode
{
public:
    SceneGraphNode();

    // Call the primitives draw function to draw the current primitive at the current transform
    void draw();

    // Query the scene looking for the closest hit, bounded by min_t and max_t
    HitRecord queryScene(Ray ray, double * min_t, double * max_t);

    // Adds a child to the current node
    void addChild(SceneGraphNode * child);
    QMatrix4x4 getCompleteTransform();

    // Gets the primitive for the current node
    SceneObject * getSceneObject();
    void setSceneObject(SceneObject * sceneObj, SceneObjectProperties * sp);

    // Destroys all the children of this node
    void destroyAll();

    // The nodes material properties
    SceneObjectProperties * sceneObjectProperties;

    // The local transform of the node
    QMatrix4x4 localTransform;

    // The children of the node
    std::vector<SceneGraphNode *> children;

    // A reference to the nodes parent
    SceneGraphNode * parent;

private:
    void draw(QMatrix4x4 transform);
    void queryScene(Ray ray, HitRecord * hitRecord, QMatrix4x4 transform);
    SceneObject * sceneObject;
};

#endif // SCENEGRAPHNODE_H
