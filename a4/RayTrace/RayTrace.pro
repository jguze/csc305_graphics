#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T16:58:59
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTrace
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    scenegraphnode.cpp \
    sceneobject.cpp \
    sphere.cpp \
    ray.cpp \
    imageviewer.cpp \
    lightsource.cpp \
    shademodel.cpp \
    lambertianshademodel.cpp \
    blinnphongshademodel.cpp \
    triangle.cpp \
    materialfactory.cpp \
    materialcombobox.cpp \
    objfilereader.cpp \
    trianglemesh.cpp \
    square.cpp \
    primitivefactory.cpp \
    arealightsource.cpp \
    lightmanager.cpp \
    raytracer.cpp \
    cameramanager.cpp \
    cube.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    scenegraphnode.h \
    sceneobject.h \
    sphere.h \
    ray.h \
    imageviewer.h \
    lightsource.h \
    shademodel.h \
    lambertianshademodel.h \
    blinnphongshademodel.h \
    triangle.h \
    materialfactory.h \
    materialcombobox.h \
    objfilereader.h \
    trianglemesh.h \
    square.h \
    primitivefactory.h \
    arealightsource.h \
    lightmanager.h \
    raytracer.h \
    cameramanager.h \
    cube.h

FORMS    += mainwindow.ui
