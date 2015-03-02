#include "materialcombobox.h"

MaterialComboBox::MaterialComboBox(QWidget *parent) :
    QComboBox(parent)
{
}

void MaterialComboBox::setOpenGLWidget(OpenGLWidget *_openglWidget)
{
    openglWidget = _openglWidget;

    for (int i = 0; i < openglWidget->materialFactory.materialSize(); i++)
    {
        addItem(openglWidget->materialFactory.getTextForMaterial((MaterialFactory::Material)i));
    }
}
