/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QGLShaderProgram>
#include "datamanager.h"
#include <gl.h>
#include <OpenGL/glu.h>
#include "linearalg.h"
#include "lightsource.h"
#include "common.h"

#define RADIUS 20
#define INIT_CYLINDER_RADIUS 20
#define INIT_CAMERA 75.0f
#define INIT_VIEW_TO 0.0f
#define INIT_ANGLE 0
#define AXIS_LENGTH 18.0f
#define VIEW_SCALE 0.05f
#define GRID_SIZE 100

class Cube;
class SolidSphere;
enum CylinderType {LINE, VERTEX, TRIANGLE};


/**
 * @brief The OpenGLWidget class The 3D widget for the views. It will render the
 * points in the dataManager to the 3D view in the proper locations.
 */
class OpenGLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:

public:
    /**
     * @brief OpenGLWidget Basic constructor that takes in the dataManager
     * @param d
     */
    explicit OpenGLWidget(DataManager * d);
    explicit OpenGLWidget(QWidget * parent, QGLWidget * shareWidget = 0);

    /**
     * @brief draw Draws all 3D points to the screen, as well as drawing the catmull-rom spline to the screen
     */
    void virtual draw();

    /**
     * @brief draw3DLine Draws a 3D line to the screen, given a starting point, and an ending point
     * @param v0 The starting 3D point of the line
     * @param v1 The ending 3D point of the line
     */
    void draw3DLine(QVector3D v0, QVector3D v1);
    void draw3DLine(Vector3 v0, Vector3 v1);
    void drawTriangle(Triangle3 triangle);

    /**
     * @brief drawAxis Draws the axis on the screen with the appropriate color
     */
    void drawAxis();

    /**
     * @brief drawGrid Draws the grid on the screen, depending on the respective planes to be drawn
     */
    void drawGrid();

    /**
     * @brief lookPrevPoint Changes the view to look at the previous point in the list. Point 0 is the origin
     */
    void lookPrevPoint();

    /**
     * @brief lookNextPoint Changes the view to look at the next point in the list. Point 0 is the origin
     */
    void lookNextPoint();

    /**
     * @brief hidePoints Prevents the points from being drawn on the screen if invoked
     */
    void hidePoints();

    /**
     * @brief hideGrid Toggles the grid from being drawn on the screen if invoked.
     */
    void hideGrid();

    /**
     * @brief hideGridXY Toggles the XY plane grid from being drawn on the screen if invoked
     */
    void hideGridXY();

    /**
     * @brief hideGridXZ Toggles the XZ plane grid from being drawn on the screen if invoked
     */
    void hideGridXZ();

    /**
     * @brief hideGridYZ Toggles the YZ plane grid from being drawn on the screen if invoked
     */
    void hideGridYZ();

    /**
     * @brief hidePointLines Toggles the lines between points from being drawn on the screen if invoked
     */
    void hidePointLines();

    /**
     * @brief hideAxis Toggles the axis from being drawn on the screen if invoked
     */
    void hideAxis();

    /**
     * @brief hideSpline Toggles the spline from being drawn on the screen if invoked
     */
    void hideSpline();

    void drawCylinder();
    void clear();
    void toggleSpecial(bool on);
    void addLight();

    /**
     * @brief currentViewedPoint The point being currently viewed. 0 defaults to the origin
     */
    int currentViewedPoint;

    /**
     * @brief viewTo The point on which the camera is viewing
     */
    Vector3 viewTo;

    /**
     * @brief dataManager A reference to all the points in the system
     */
    DataManager * dataManager;
    double cylinder_radius;

    CylinderType cylinderType;
    GLenum lights[8];
    Shape shape;
    QVector<FrenetCrossSection> crossSectionList;
    QVector<Triangle3> lids;
    FrenetCrossSection * currentCrossSection;
    Cube * cube;
    bool drawCube;
    bool drawLids;

protected:
    /**
     * @brief mousePressEvent
     * @param e
     */
    void mousePressEvent(QMouseEvent *e);

    /**
     * @brief mouseReleaseEvent
     * @param e
     */
    void mouseReleaseEvent(QMouseEvent *e);

    /**
     * @brief mouseMoveEvent
     * @param e
     */
    void mouseMoveEvent(QMouseEvent * e);

    /**
     * @brief initializeGL
     */
    void initializeGL();

    /**
     * @brief resizeGL
     * @param w
     * @param h
     */
    void resizeGL(int w, int h);

    /**
     * @brief paintGL
     */
    void paintGL();

    /**
     * @brief lastPoint The previous point that was being pressed
     */
    QPoint lastPoint;

    QVector<Triangle3> cylinderList;
    bool special;

private:

    /**
     * @brief rotate Rotates a point around the Y and Z axis given a difference in points
     * @param change The new changed point value
     * @param original The original point value
     */
    void rotate(QPoint change, QPoint original);

    /**
     * @brief scale Scales the view depending on the changed values from a mouse draw
     * @param change
     * @param original
     */
    void scale(QPoint change, QPoint original);

    /**
     * @brief changeView Rotates a point around the X axis
     * @param change New changed point value
     * @param original Original point value
     */
    void changeView(QPoint change, QPoint original);

    /**
     * @brief rotateX Rotates a vector around the X axis by some radians
     * @param vec
     * @param rad
     */
    void rotateX(QVector3D * vec, double rad);
    void rotateY(QVector3D * vec, double rad);
    void rotateZ(QVector3D * vec, double rad);

    void setLighting();

    /**
     * @brief cameraPos The current camera position
     */
    QVector3D cameraPos;

    /**
     * @brief isRotating A boolean to determine if we are rotating the view in the y or z axis
     */
    bool isRotating;

    /**
     * @brief isScaling A boolean to determine if we are scaling the view
     */
    bool isScaling;

    /**
     * @brief isViewing A boolean to determine if we are rotating the view in the x axis
     */
    bool isViewing;

    // A set of booleans to toggle visibility of objects on the screen
    bool isAxisVisible;
    bool isGridXZVisible;
    bool isGridXYVisible;
    bool isGridYZVisible;
    bool isPointLinesVisible;
    bool isPointsVisible;
    bool isSplineVisible;

    bool canDrawCylinder;

    /**
     * @brief scaleMatrix A scale to be able to view anything drawn on the screen in the proper locations
     */
    Matrix33 scaleMatrix;
    int cubeFrame;
    int cubeCenter;


    /**
     * @brief sphere A sphere in memory that can be drawn in multiple places
     */
    SolidSphere * sphere;
};

/**
 * @brief The SolidSphere class Sphere code from datenwolf found on StackOverflow here:
 * http://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c
 */
class SolidSphere
{
protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;

public:
    SolidSphere(float radius, unsigned int rings, unsigned int sectors)
    {
        float const R = 1./(float)(rings-1);
        float const S = 1./(float)(sectors-1);
        unsigned int r, s;

        vertices.resize(rings * sectors * 3);
        normals.resize(rings * sectors * 3);
        texcoords.resize(rings * sectors * 2);
        std::vector<GLfloat>::iterator v = vertices.begin();
        std::vector<GLfloat>::iterator n = normals.begin();
        std::vector<GLfloat>::iterator t = texcoords.begin();
        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
                float const y = sin( -M_PI_2 + M_PI * r * R );
                float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
                float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

                *t++ = s*S;
                *t++ = r*R;

                *v++ = x * radius;
                *v++ = y * radius;
                *v++ = z * radius;

                *n++ = x;
                *n++ = y;
                *n++ = z;
        }

        indices.resize(rings * sectors * 4);
        std::vector<GLushort>::iterator i = indices.begin();
        for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
                *i++ = r * sectors + s;
                *i++ = r * sectors + (s+1);
                *i++ = (r+1) * sectors + (s+1);
                *i++ = (r+1) * sectors + s;
        }
    }

    void draw(GLfloat x, GLfloat y, GLfloat z)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(x,y,z);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glNormalPointer(GL_FLOAT, 0, &normals[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
        glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
        glPopMatrix();
    }
};

class Cube
{
public:
    Cube(double _radius) : radius(_radius) {
        double d = _radius/2;
        Vector3 tl1(-d,d,-d);
        Vector3 tl2(d,d,-d);
        Vector3 tr1(-d,d,d);
        Vector3 tr2(d,d,d);

        Vector3 bl1(-d,-d,-d);
        Vector3 bl2(d,-d,-d);
        Vector3 br1(-d,-d,d);
        Vector3 br2(d,-d,d);

        faces.clear();
        faces.push_back(Square3(bl1,br1,tl1,tr1));
        faces.push_back(Square3(tl1, tr1, tl2, tr2));
        faces.push_back(Square3(bl2, br2, tl2, tr2));
        faces.push_back(Square3(bl2, br2, bl1, br1));
        faces.push_back(Square3(bl2, bl1, tl2, tl1));
        faces.push_back(Square3(br1, br2, tr1, tr2));
        center = Vector3(0, 0, 0);
        direction = Vector3(1, 0, 0);
    }

    Cube(Square3 _s) {
        faces.clear();
        faces.push_back(_s);        
//        Matrix33 translateTopLeft = linalg::translate3(_s.topLeft * -1);




//        _s = _s * *linalg::rotateAxisUVW((_s.topLeft + (_s.topRight * -1)).normalize(), 90);
//        faces.push_back(_s);

//        _s = _s * *linalg::rotateAxisUVW((_s.topLeft + (_s.topRight * -1)).normalize(), 90);
//        faces.push_back(_s);

//        _s = _s * *linalg::rotateAxisUVW((_s.btmLeft + (_s.btmRight * -1)).normalize(), -90);
//        faces.push_back(_s);

//        _s = _s * *linalg::rotateAxisUVW((_s.topLeft + (_s.topRight * -1)).normalize(), 90);
//        faces.push_back(_s);
    }

    double radius;
    QVector<Square3> faces;
    Vector3 center;
    Vector3 direction;
};

#endif // MAINWIDGET_H
