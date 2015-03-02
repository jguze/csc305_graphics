#ifndef MATERIALCOMBOBOX_H
#define MATERIALCOMBOBOX_H

#include <QComboBox>
#include <openglwidget.h>

class MaterialComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit MaterialComboBox(QWidget *parent = 0);

signals:

public slots:

public:
    void setOpenGLWidget(OpenGLWidget * _openglWidget);
private:
    OpenGLWidget * openglWidget;
};

#endif // MATERIALCOMBOBOX_H
