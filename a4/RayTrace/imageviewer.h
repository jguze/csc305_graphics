#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGLWidget>
#include <GL/gl.h>

// The image viewer loads the finished picture and displays it to the user
class ImageViewer : public QGLWidget
{
public:
    ImageViewer(QWidget *parent);

    void displayImage(QImage glImage);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    double renderWidth;
    double renderHeight;
    QImage image;
};

#endif // IMAGEVIEWER_H
