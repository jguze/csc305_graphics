#include "scenegraphnode.h"

SceneGraphNode::SceneGraphNode()
{
    sceneObject = NULL;
    parent = NULL;
    localTransform = QMatrix4x4();
}

void SceneGraphNode::draw()
{
    draw(QMatrix4x4());
}

void SceneGraphNode::draw(QMatrix4x4 transform)
{
    transform = localTransform * transform;
    if (sceneObject != NULL)
    {
        sceneObject->drawGeometry(transform, sceneObjectProperties);
    }

    for (std::vector<SceneGraphNode *>::iterator it = children.begin(); it != children.end(); it++)
    {
        (*it)->draw(transform);
    }
}

HitRecord SceneGraphNode::queryScene(Ray ray, double * min_t, double * max_t)
{
    HitRecord hitRecord(false);
    hitRecord.min_t = *min_t;
    hitRecord.t = *max_t;
    queryScene(ray, &hitRecord, localTransform);
    return hitRecord;
}

void SceneGraphNode::queryScene(Ray ray, HitRecord * hitRecord, QMatrix4x4 transform)
{
    HitRecord hit;
    hit.t = hitRecord->t;
    hit.min_t = hitRecord->min_t;
    hit.hit = false;
    transform = localTransform * transform;
    if (sceneObject != NULL)
    {
//        Ray inverseRay;
//        QMatrix4x4 inverseTransform = transform.inverted();
//        inverseRay.origin = inverseTransform * ray.origin;
//        inverseRay.direction = inverseTransform * ray.direction;
        sceneObject->intersects(ray, transform, &hit);
        if (hit.hit)
        {
            hit.sceneObjectProperties = sceneObjectProperties;
            hit.transform = transform;
            hit.sceneObject = sceneObject;
            //QMatrix4x4 transpose = inverseTransform.transposed();
            //transpose.setRow(3, QVector4D(0, 0, 0, 1));
            //hit.normal = (transpose * sceneObject->getNormal(inverseRay.getPoint(hit.t), transform, hit)).normalized();
            *hitRecord = hit;
        }
    }

    for (std::vector<SceneGraphNode *>::iterator it = children.begin(); it != children.end(); it++)
    {
        (*it)->queryScene(ray, hitRecord, transform);
    }
}

void SceneGraphNode::addChild(SceneGraphNode *child)
{
    child->parent = this;
    children.push_back(child);
}

QMatrix4x4 SceneGraphNode::getCompleteTransform()
{
    if (parent == NULL)
    {
        return localTransform;
    }

    return localTransform * parent->getCompleteTransform();
}

SceneObject * SceneGraphNode::getSceneObject()
{
    return sceneObject;
}

void SceneGraphNode::setSceneObject(SceneObject *sceneObj, SceneObjectProperties *sp)
{
    sceneObject = sceneObj;
    sceneObjectProperties = sp;
}

void SceneGraphNode::destroyAll()
{
    for (std::vector<SceneGraphNode *>::iterator it = children.begin(); it != children.end(); it++)
    {
        (*it)->destroyAll();
        delete (*it);
    }
    children.clear();
}
