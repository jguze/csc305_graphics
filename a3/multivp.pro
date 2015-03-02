QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    openGLWidget.cpp \
    datamanager.cpp \
    flatwidget.cpp \
    flatwidgetxy.cpp \
    flatwidgetxz.cpp \
    flatwidgetyz.cpp \
    linearalg.cpp \
    lightsource.cpp


    QT += opengl

    SOURCES +=

    HEADERS += \
    datamanager.h \
    flatwidget.h \
    flatwidgetxy.h \
    flatwidgetxz.h \
    flatwidgetyz.h \
    linearalg.h \
    lightsource.h \
    common.h

    RESOURCES += \
        shaders.qrc \
        textures.qrc


# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    openGLWidget.h
