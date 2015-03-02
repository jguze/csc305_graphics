#include "imageviewer.h"
#include <QDebug>

ImageViewer::ImageViewer(QWidget *parent) :
    QGLWidget(parent)
{
}

void ImageViewer::initializeGL()
{
    //Background color will be white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel( GL_FLAT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPointSize(5);
}

void ImageViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (image.width() != 0)
    {
        glRasterPos2i(0,0);
        glDrawPixels(image.width(), image.height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
        glFlush();
    }
}

/* 2D */
void ImageViewer::resizeGL( int w, int h )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0,GLdouble(w),0,GLdouble(h),-10.0,10.0);
    glFlush();
    glMatrixMode(GL_MODELVIEW);
    glViewport( 0, 0, (GLint)w, (GLint)h );
    renderWidth = w;
    renderHeight = h;
}

void ImageViewer::displayImage(QImage glImage)
{
    image = glImage;
    update();
}
