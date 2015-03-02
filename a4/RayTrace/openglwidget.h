#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QWidget>
#include <QVector3D>
#include <GL/gl.h>
#include <GL/glu.h>
#include <sphere.h>
#include <triangle.h>
#include <scenegraphnode.h>
#include <ray.h>
#include <QFileDialog>
#include <imageviewer.h>
#include <QMouseEvent>
#include <lightsource.h>
#include <lambertianshademodel.h>
#include <blinnphongshademodel.h>
#include <materialfactory.h>
#include <objfilereader.h>
#include <QProgressBar>
#include <time.h>
#include <square.h>
#include <primitivefactory.h>
#include <lightmanager.h>
#include <cameramanager.h>

#define AXIS_LENGTH 50
#define STRAFE_AMOUNT 1

/*
 * The bulkiest of classes. This OpenGL widget handles all OpenGL UI as well as
 * the main UI itself. The main Ray Trace loop is here. Would be better to move it elsewhere at the end.
 */
class OpenGLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget * parent);

    // Begins raytracing all objects in the current scene defined by the root node
    void rayTrace();

    // Store a reference to the image viewer so that we can see our image
    void setImageViewer(ImageViewer * _imageViewer);

    // Store a reference to the progress bar
    void setProgressBar(QProgressBar * _pBar);

    // Enable keyboard presses at this level
    void handleKeyPress(QKeyEvent * e);

    int renderWidth;
    int renderHeight;

    // The default background colour of the image
    QVector3D backgroundColour;
    MaterialFactory materialFactory;
    PrimitiveFactory primitiveFactory;

    void printMatrix(QMatrix4x4 m);


signals:

public slots:
    void raytraceImage();
    void changeShadeModelLambertian(bool);
    void changeShadeModelBlinnPhong(bool);
    void saveImage();
    void loadBackgroundTexture();
    void changeMaterial(int);
    void loadObjFile();
    void changeAntiAlias(int);
    void clearScreen();
    void changeDepthOfField(int);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mouseMoveEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);

private:

    // Initialize the scene with a set of objects and lights
    void initializeScene();

    // Draw the axis in the OpenGL view
    void drawAxis();

    // Draw an arbitrary 3D line
    void draw3DLine(QVector3D v0, QVector3D v1);

    // Draw all the lights in the OpenGL view
    void drawLight();

    void prepareImageDisplay(QImage * image);

    // Initialize the lights in the system
    void initializeLights();

    // Initialize any background textures
    void initializeBackgroundTexture();

    // Returns a jittered random number based on i
    double jitterValue(int i);

    // Gets the current background colour
    QVector3D getBackgroundColour(int i, int j);

    void scale(QPoint desc, QPoint original);
    void rotate(QPoint change, QPoint original);

    // The scene graph. It starts at the root, and procedes down to the children recursively
    SceneGraphNode * root;

    QImage qtImage;
    ImageViewer * imageViewer;

    // The current shading model being used
    ShadeModel * shadeModel;
    QImage backgroundTexture;
    QImage scaledBackgroundTexture;
    ObjFileReader objFileReader;
    QProgressBar * progressBar;
    std::vector<double> randomNumbers;
    LightManager lightManager;
    CameraManager cameraManager;

    double focalLength;
    double sampleSize; // used for antialiasing
    double sampleSize2;

    QPoint lastPoint;
    bool isRotating;
    bool isScaling;
    bool isDepthOfField;
};

#endif // OPENGLWIDGET_H
