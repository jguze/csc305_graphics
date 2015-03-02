#ifndef MATERIALFACTORY_H
#define MATERIALFACTORY_H

#include <QString>
#include <sceneobject.h>

#define MATERIAL_SIZE 24

/*
 * A factory class that holds all the materials in the system.
 * This ensures that we don't create multiple material objects for objects that share
 * the same material
 */
class MaterialFactory
{

public:
    enum Material {
        BRASS,
        BRONZE,
        POLISHEDBRONZE,
        CHROME,
        COPPER,
        POLISHEDCOPPER,
        GOLD,
        POLISHEDGOLD,
        PEWTER,
        SILVER,
        POLISHEDSILVER,
        EMERALD,
        JADE,
        OBSIDIAN,
        PEARL,
        RUBY,
        TURQUOISE,
        BLACKPLASTIC,
        MIRROR,
        GLASS,
        BLUE,
        RED,
        GREEN,
        YELLOW
    };

    MaterialFactory();

    // Get the material properties given a Material enum.
    SceneObjectProperties * getMaterialProperties(Material m);
    QString getTextForMaterial(Material m) {return MaterialStrings[m];}
    int materialSize() {return MATERIAL_SIZE;}
private:
    static const QString MaterialStrings[MATERIAL_SIZE];
    std::vector<SceneObjectProperties *> materialProperties;

};



#endif // MATERIALFACTORY_H
