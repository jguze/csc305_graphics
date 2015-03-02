#include "lightmanager.h"

LightManager::LightManager()
{
}

void LightManager::addLight(LightSource light)
{
    pointLights.push_back(light);
}

void LightManager::addAreaLight(AreaLightSource areaLight)
{
    areaLights.push_back(areaLight);
}

void LightManager::updateLights()
{
    allLights.clear();
    for (std::vector<LightSource>::iterator lit = pointLights.begin(); lit != pointLights.end(); lit++)
    {
        allLights.push_back(*lit);
    }

    for (std::vector<AreaLightSource>::iterator alit = areaLights.begin(); alit != areaLights.end(); alit++)
    {
//        alit->randomize();
//        for (int i = 0; i < alit->numLights; i++)
//        {
//            allLights.push_back(alit->pointLights[alit->randomNumbers[i]]);
//        }
        for (std::vector<LightSource>::iterator aplit = alit->pointLights.begin(); aplit != alit->pointLights.end(); aplit++)
        {
            allLights.push_back(*aplit);
        }
    }
}
