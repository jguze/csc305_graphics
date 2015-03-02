#include "arealightsource.h"

AreaLightSource::AreaLightSource()
{
}

AreaLightSource::AreaLightSource(QVector3D _position, QVector3D _topLeft, QVector3D _bottomRight, double _intensity, double _ambientIntensity, int n, PrimitiveFactory * _primitiveFactory)
{
    position = _position;
    edgeA = (_topLeft - position);
    edgeB = (_bottomRight - position);
    intensity = _intensity;
    ambientIntensity = _ambientIntensity;
    numLights = n;
    primitiveFactory = _primitiveFactory;
    randomNumbers.resize(n);
    square = primitiveFactory->getSceneObject(PrimitiveFactory::FLAT_SQUARE);
    generatePoints();
}

void AreaLightSource::generatePoints()
{
    pointLights.clear();
    QVector3D pos;
    int n = numLights * numLights;
    for (int i = 0; i < numLights; i++)
    {
        for (int j = 0; j < numLights; j++)
        {
            pos = position + (((double)std::rand() / RAND_MAX) * edgeA) +
                    (((double)std::rand() / RAND_MAX) * edgeB);
            pointLights.push_back(LightSource(pos, intensity / n, ambientIntensity, primitiveFactory));
        }
    }
    randomize();
}

QVector3D AreaLightSource::getMiddlePos()
{
    return ((edgeA - edgeB) / 2) + edgeB + QVector3D(0, position.y(), 0);
}

void AreaLightSource::randomize()
{
    for (int i = 0; i < numLights; i++)
    {
        randomNumbers[i] = ((int)std::rand()) % numLights;
    }
}
