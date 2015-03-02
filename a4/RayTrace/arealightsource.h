#ifndef AREALIGHTSOURCE_H
#define AREALIGHTSOURCE_H

#include <lightsource.h>

/*
 * A basic Area Light source. It is actually composed of numLights random point lights in the area defined be the topLeft, bottomRight and position as bottomLeft.
 */
class AreaLightSource
{
public:
    AreaLightSource();

    // The area light source takes in the same basic values as a normal light along with the position and edge vectors
    AreaLightSource(QVector3D _position, QVector3D _topLeft, QVector3D _bottomRight, double _intensity, double _ambientIntensity, int n, PrimitiveFactory * _primitiveFactory);

    // Generates the random set of points in the area
    void generatePoints();

    // Re-randomizes all the points
    void randomize();

    // Get's the absolute middle position of the area light
    QVector3D getMiddlePos();

    // The bottom left of the area light
    QVector3D position;

    // The complete intensity of the whole area light. Every point light in the area light has intensity of intensity / N
    double intensity;
    double ambientIntensity;
    int numLights;
    QVector3D edgeA;
    QVector3D edgeB;
    std::vector<LightSource> pointLights;
    PrimitiveFactory * primitiveFactory;
    std::vector<int> randomNumbers;
    SceneObject * square;
};

#endif // AREALIGHTSOURCE_H
