#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <arealightsource.h>

// Handles all lighting data, along with creating the final light array. Can hold
// both area lights and point lights.
class LightManager
{
public:
    LightManager();
    void addLight(LightSource light);
    void addAreaLight(AreaLightSource areaLight);
    void updateLights();

    std::vector<AreaLightSource> areaLights;
    std::vector<LightSource> pointLights;
    std::vector<LightSource> allLights;
};

#endif // LIGHTMANAGER_H
