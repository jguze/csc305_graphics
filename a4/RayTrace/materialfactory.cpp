#include "materialfactory.h"

MaterialFactory::MaterialFactory()
{
    materialProperties.resize(MATERIAL_SIZE);

    materialProperties[BRASS] = new SceneObjectProperties(QVector3D(0.780392, 0.568627, 0.113725),27.8974,QVector3D(0.780392, 0.568627, 0.113725),QVector3D(0.329412, 0.223529, 0.027451));
    materialProperties[BRONZE] = new SceneObjectProperties(QVector3D(0.714, 0.4284, 0.18144),25.6,QVector3D(0.714, 0.4284, 0.18144),QVector3D(0.2125, 0.1275, 0.054));
    materialProperties[POLISHEDBRONZE] = new SceneObjectProperties(QVector3D(0.4, 0.2368, 0.1036),76.8,QVector3D(0.4, 0.2368, 0.1036),QVector3D(0.25, 0.148, 0.06475));
    materialProperties[CHROME] = new SceneObjectProperties(QVector3D(0.4, 0.4, 0.4),76.8,QVector3D(0.4, 0.4, 0.4),QVector3D(0.25, 0.25, 0.25));
    materialProperties[COPPER] = new SceneObjectProperties(QVector3D(0.7038, 0.27048, 0.0828),12.8,QVector3D(0.7038, 0.27048, 0.0828),QVector3D(0.19125, 0.0735, 0.0225));
    materialProperties[POLISHEDCOPPER] = new SceneObjectProperties(QVector3D(0.5508, 0.2118, 0.066),51.2,QVector3D(0.5508, 0.2118, 0.066),QVector3D(0.2295, 0.08825, 0.0275));
    materialProperties[GOLD] = new SceneObjectProperties(QVector3D(0.75164, 0.60648, 0.22648),51.2,QVector3D(0.75164, 0.60648, 0.22648),QVector3D(0.24725, 0.1995, 0.0745));
    materialProperties[POLISHEDGOLD] = new SceneObjectProperties(QVector3D(0.34615, 0.3143, 0.0903),83.2,QVector3D(0.34615, 0.3143, 0.0903),QVector3D(0.24725, 0.2245, 0.0645));
    materialProperties[PEWTER] = new SceneObjectProperties(QVector3D(0.427451, 0.470588, 0.541176),9.84615,QVector3D(0.427451, 0.470588, 0.541176),QVector3D(0.105882, 0.058824, 0.113725));
    materialProperties[SILVER] = new SceneObjectProperties(QVector3D(0.50754, 0.50754, 0.50754),51.2,QVector3D(0.50754, 0.50754, 0.50754),QVector3D(0.19225, 0.19225, 0.19225));
    materialProperties[POLISHEDSILVER] = new SceneObjectProperties(QVector3D(0.2775, 0.2775, 0.2775),89.6,QVector3D(0.2775, 0.2775, 0.2775),QVector3D(0.23125, 0.23125, 0.23125));
    materialProperties[EMERALD] = new SceneObjectProperties(QVector3D(0.07568, 0.61424, 0.07568),76.8,QVector3D(0.07568, 0.61424, 0.07568),QVector3D(0.0215, 0.1745, 0.0215));
    materialProperties[JADE] = new SceneObjectProperties(QVector3D(0.54, 0.89, 0.63),12.8,QVector3D(0.54, 0.89, 0.63),QVector3D(0.135, 0.2225, 0.1575));
    materialProperties[OBSIDIAN] = new SceneObjectProperties(QVector3D(0.18275, 0.17, 0.22525),38.4,QVector3D(0.18275, 0.17, 0.22525),QVector3D(0.05375, 0.05, 0.06625));
    materialProperties[PEARL] = new SceneObjectProperties(QVector3D(1, 0.829, 0.829),11.264,QVector3D(1, 0.829, 0.829),QVector3D(0.25, 0.20725, 0.20725));
    materialProperties[RUBY] = new SceneObjectProperties(QVector3D(0.61424, 0.04136, 0.04136),76.8,QVector3D(0.61424, 0.04136, 0.04136),QVector3D(0.1745, 0.01175, 0.01175));
    materialProperties[TURQUOISE] = new SceneObjectProperties(QVector3D(0.396, 0.74151, 0.69102),12.8,QVector3D(0.396, 0.74151, 0.69102),QVector3D(0.1, 0.18725, 0.1745));
    materialProperties[BLACKPLASTIC] = new SceneObjectProperties(QVector3D(0.01, 0.01, 0.01),32,QVector3D(0.01, 0.01, 0.01),QVector3D(0, 0, 0));
    materialProperties[BLACKPLASTIC] = new SceneObjectProperties(QVector3D(0.01, 0.01, 0.01),32,QVector3D(0.01, 0.01, 0.01),QVector3D(0, 0, 0));
    materialProperties[MIRROR] = new SceneObjectProperties(QVector3D(0,0,0), 20, QVector3D(1,1,1), QVector3D(0,0,0));
    materialProperties[MIRROR]->mirror = 0;
    materialProperties[GLASS] = new SceneObjectProperties();
    materialProperties[GLASS]->refractionIndex = 1.50;
    materialProperties[BLUE] = new SceneObjectProperties(QVector3D(0.2, 0.2, 1.0), 1, QVector3D(0.01, 0.01, 0.01), QVector3D(0.5, 0.5, 0.5));
    materialProperties[RED] = new SceneObjectProperties(QVector3D(1.0, 0.2, 0.2), 1, QVector3D(0.01, 0.01, 0.01), QVector3D(0.5, 0.5, 0.5));
    materialProperties[GREEN] = new SceneObjectProperties(QVector3D(0.2, 1.0, 0.2), 1, QVector3D(0.01, 0.01, 0.01), QVector3D(0.5, 0.5, 0.5));
    materialProperties[YELLOW] = new SceneObjectProperties(QVector3D(1.0, 1.0, 0.2), 1, QVector3D(0.01, 0.01, 0.01), QVector3D(0.5, 0.5, 0.5));

}

SceneObjectProperties * MaterialFactory::getMaterialProperties(Material m)
{
    return materialProperties[m];
}

const QString MaterialFactory::MaterialStrings[MATERIAL_SIZE] = {"Brass", "Bronze", "Polished Bronze", "Chrome",
                                             "Copper", "Polished Copper", "Gold", "Polished Gold",
                                             "Pewter", "Silver", "Polished Silver", "Emerald", "Jade",
                                             "Obsidian", "Pearl", "Ruby", "Turquoise", "Black Plastic", "Mirror", "Glass", "Blue",
                                                                "Red", "Green", "Yellow"};
