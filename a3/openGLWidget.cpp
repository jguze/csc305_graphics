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

#include "openGLWidget.h"
#include <QMouseEvent>
#include <math.h>

const double RadPerPixel = - 0.01;
const double MovePerPixel = - 0.1;
const double lim=0.0005;

OpenGLWidget::OpenGLWidget(DataManager * d)
{
    dataManager = d;
    cameraPos.setX(INIT_CAMERA);
    cameraPos.setY(INIT_CAMERA);
    cameraPos.setZ(INIT_CAMERA);
    viewTo.x = viewTo.y = viewTo.z = INIT_VIEW_TO;
    cylinder_radius = INIT_CYLINDER_RADIUS;
    isRotating = isScaling = isViewing = false;
    isAxisVisible = isGridXZVisible = isPointLinesVisible = isPointsVisible = isSplineVisible = true;
    isGridXYVisible = isGridYZVisible = false;
    canDrawCylinder = false;
    special = false;
    cylinderType = TRIANGLE;
    currentViewedPoint = 0;
    sphere = new SolidSphere(0.6, 12, 24);

    scaleMatrix = *linalg::scale3(VIEW_SCALE, VIEW_SCALE, VIEW_SCALE);
    lights[0] = GL_LIGHT0;
    lights[1] = GL_LIGHT1;
    lights[2] = GL_LIGHT2;
    lights[3] = GL_LIGHT3;
    lights[4] = GL_LIGHT4;
    lights[5] = GL_LIGHT5;
    lights[6] = GL_LIGHT6;
    lights[7] = GL_LIGHT7;
    cubeFrame = 0;
    shape = CIRCLE;
    drawCube = false;
    drawLids = true;
//    cubeCenter = Vector3(0,0,0);
    cube = new Cube(100.0);
    currentCrossSection = NULL;

}

OpenGLWidget::OpenGLWidget(QWidget *parent, QGLWidget * shareWidget)
    : QGLWidget(parent, shareWidget)
{
}


//! [0]
void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        isRotating = true;
    } else if (e->button() == Qt::RightButton)
    {
        isScaling = true;
    } else if (e->button() == Qt::MiddleButton)
    {
        isViewing = true;
    }
    lastPoint = e->pos();
    update();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && isRotating)
    {
        rotate(e->pos(), lastPoint);
        isRotating = false;
    } else if (e->button() == Qt::RightButton && isScaling)
    {
        scale(e->pos(), lastPoint);
        isScaling = false;
    } else if (e->button() == Qt::MiddleButton && isViewing)
    {
        changeView(e->pos(), lastPoint);
        isViewing = false;
    }
    update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent * e)
{
    if ((e->buttons() & Qt::LeftButton) && isRotating)
    {
        rotate(e->pos(), lastPoint);
    } else if ((e->buttons() & Qt::RightButton) && isScaling)
    {
        scale(e->pos(), lastPoint);
    } else if ((e->buttons() & Qt::MiddleButton) && isViewing)
    {
        changeView(e->pos(), lastPoint);
    }
    lastPoint = e->pos();

    update();
}

void OpenGLWidget::initializeGL()
{
    glClearColor( 0,0,0,0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_LIGHTING);

  // GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
   //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
   glFrontFace(GL_CCW);
   addLight();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport( 0, 0, (GLint)w, (GLint)h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 1500 );
    glMatrixMode( GL_MODELVIEW );
}

void OpenGLWidget::paintGL()
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0,1.0,0);
    glLoadIdentity();
    gluLookAt(cameraPos.x(), cameraPos.y(), cameraPos.z(), viewTo.x, viewTo.y, viewTo.z, 0.0, 1.0, 0.0);
    glRotatef( 0, 1.0, 0.0, 0.0);
    glRotatef( 0, 0.0, 1.0, 0.0);
    glRotatef( 0, 0.0, 0.0, 1.0);
    if (crossSectionList.size() > 0)
    {
        cubeFrame = (cubeFrame + 1) % (crossSectionList.size() * 3);
        currentCrossSection = new FrenetCrossSection(crossSectionList[cubeFrame / 3]);
    } else {
        cubeFrame = 0;
        currentCrossSection = NULL;
    }
    setLighting();
    drawGrid();
    drawAxis();
    draw();

}

void OpenGLWidget::rotateX(QVector3D * vec, double rad)
{
    double degree = rad * RAD_TO_DEGREE;
    Vector3 v = *linalg::rotate3X(degree) * Vector3(vec->x(), vec->y(), vec->z());
    vec->setX(v.x);
    vec->setY(v.y);
    vec->setZ(v.z);
}

void OpenGLWidget::rotateY(QVector3D * vec, double rad)
{
    double degree = rad * RAD_TO_DEGREE;
    Vector3 v = *linalg::rotate3Y(degree) * Vector3(vec->x(), vec->y(), vec->z());
    vec->setX(v.x);
    vec->setY(v.y);
    vec->setZ(v.z);
}

void OpenGLWidget::rotateZ(QVector3D * vec, double rad)
{
    double degree = rad * RAD_TO_DEGREE;
    Vector3 v = *linalg::rotate3Z(degree) * Vector3(vec->x(), vec->y(), vec->z());
    vec->setX(v.x);
    vec->setY(v.y);
    vec->setZ(v.z);
}

void OpenGLWidget::rotate(QPoint change, QPoint original)
{
    double yRot = (change.x() - original.x()) * RadPerPixel;
    double zRot = (change.y() - original.y()) * RadPerPixel;

    rotateZ(&cameraPos, zRot);
    rotateY(&cameraPos, yRot);
}

void OpenGLWidget::scale(QPoint change, QPoint original)
{
    double length = sqrt( pow(cameraPos.x(), 2) + pow(cameraPos.y(), 2));
    double newLength = length + (change.y() - original.y()) * MovePerPixel;

    if (newLength > lim)
    {
        double ratio = newLength / length;
        cameraPos.setX(cameraPos.x() * ratio);
        cameraPos.setY(cameraPos.y() * ratio);
        cameraPos.setZ(cameraPos.z() * ratio);
    }
}

void OpenGLWidget::changeView(QPoint change, QPoint original)
{
//    double yDir = (change.x() - original.x()) * 0.5;
//    double xDir = (change.y() - original.y()) * 0.5;

//    angle.setX(angle.x() + xDir); //azimuth (yaw)
//    angle.setY(angle.y() + yDir); //polar (pitch)

//    viewTo.x = sin(angle.y()) * cos(angle.x());
//    viewTo.y = sin(angle.y()) * sin(angle.x());
//    viewTo.z = cos(angle.y());

    double xRot = (change.x() - original.x()) * RadPerPixel;
    rotateX(&cameraPos, xRot);
}

void OpenGLWidget::draw()
{
    glColor3f(0.85, 0.0, 0.2);
    QVector3D point;
    QVector3D prevPoint;
    bool firstPoint = true;
    Vector3 scaleTemp;
    for (QVector<QVector3D *>::iterator it = dataManager->points.begin(); it != dataManager->points.end(); it++)
    {
        scaleTemp = scaleMatrix * Vector3((*it)->x(), (*it)->y(), (*it)->z());
        point = QVector3D(scaleTemp.x, scaleTemp.y, scaleTemp.z);
        if (isPointsVisible)
        {
            sphere->draw(point.x(), point.y(), point.z());
        }
        if (!firstPoint)
        {
            if (isPointLinesVisible)
            {
                draw3DLine(point, prevPoint);
            }
        } else {
            firstPoint = false;
        }
        prevPoint = point;
    }

    Vector3 tempLight;
    for (QVector<LightSource>::iterator it = dataManager->lights.begin(); it != dataManager->lights.end(); it++)
    {
        tempLight = scaleMatrix * QVector3D(it->position);
        glColor3f(1.0, 1.0, 1.0);
        sphere->draw(tempLight.x, tempLight.y, tempLight.z);
    }

    if (!isSplineVisible)
    {
        return;
    }
    glColor3f(0, 1.0, 1.0);
//    float color[] = {0, 1.0, 1.0, 1.0};
//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    Vector3 catmullVector;
    Vector3 prevCatmull;
    firstPoint = true;
    QVector<Vector3> catmullList = dataManager->calculateCatmullRom();
    for (QVector<Vector3>::iterator it = catmullList.begin(); it != catmullList.end(); it++)
    {
        catmullVector = scaleMatrix * (*it);
        if (!firstPoint)
        {
            draw3DLine(QVector3D(catmullVector.x, catmullVector.y, catmullVector.z), QVector3D(prevCatmull.x, prevCatmull.y, prevCatmull.z));
        } else {
            firstPoint = false;
        }
        prevCatmull = catmullVector;
    }

    Vector3 pSurface;
    Vector3 prevpSurface;
    firstPoint = true;
    float specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
    glMateriali(GL_FRONT, GL_SHININESS, 96);
    Triangle3 temp;
    switch(cylinderType)
    {
        case TRIANGLE:
            for (QVector<Triangle3>::iterator pit = cylinderList.begin(); pit != cylinderList.end(); pit++)
            {
                temp = (*pit);
                temp.x = scaleMatrix * temp.x;
                temp.y = scaleMatrix * temp.y;
                temp.z = scaleMatrix * temp.z;
                drawTriangle(temp);
            }
            if (drawLids)
            {
                for (QVector<Triangle3>::iterator lit = lids.begin(); lit != lids.end(); lit++)
                {
                    temp = (*lit);
                    temp.x = scaleMatrix * temp.x;
                    temp.y = scaleMatrix * temp.y;
                    temp.z = scaleMatrix * temp.z;
                    drawTriangle(temp);
                }
            }
            break;
        case VERTEX:
            for (QVector<Triangle3>::iterator pit = cylinderList.begin(); pit != cylinderList.end(); pit++)
            {
                for (int i = 0; i < 3; i++)
                {
                    pSurface = scaleMatrix * (*pit)[i];
                    glBegin(GL_POINTS);
                    glVertex3f(pSurface.x, pSurface.y, pSurface.z);
                    glEnd();
                }
            }
            break;
        case LINE:
            for (QVector<Triangle3>::iterator pit = cylinderList.begin(); pit != cylinderList.end(); pit++)
            {
                for (int i = 0; i < 3; i++)
                {
                    pSurface = scaleMatrix * (*pit)[i];
                    if (!firstPoint)
                    {
                       draw3DLine(QVector3D(prevpSurface.x, prevpSurface.y, prevpSurface.z), QVector3D(pSurface.x, pSurface.y, pSurface.z));

                    } else {
                       firstPoint = false;
                    }
                    prevpSurface = pSurface;
                }
            }
            break;
        default:
            break;
    }

    if (currentCrossSection == NULL || !drawCube)
        return;

    float specReflectionCube[] = { 0.0001f, 0.0001f, 0.0001f, 0.5f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specReflectionCube);
    glMateriali(GL_FRONT, GL_SHININESS, 1);
    Vector3 v;
    Vector3 square_normal;
    Matrix44 translateCenter = *linalg::translate4(currentCrossSection->curvePoint);
    Matrix33 rotateY;
    Matrix33 rotateZ;
    for (QVector<Square3>::iterator sit = cube->faces.begin(); sit != cube->faces.end(); sit++)
    {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 5; i++)
        {
            v = (*sit)[i];
//            v = *linalg::rotate4Y(linalg::angleBetweenVectors(Vector3(currentCrossSection->tangent.x, 0, 0), Vector3(1,0,0))) * v; //Angle to x
//            v = *linalg::rotate4Z(linalg::angleBetweenVectors(Vector3(0, currentCrossSection->tangent.y, 0), Vector3(0,1,0))) * v;
//            v = linalg::rotateAToB(currentCrossSection->tangent, cube->direction) * v;
            v = currentCrossSection->calculatePoint(v);
//            v = translateCenter * v;
            v = scaleMatrix * v;
            square_normal = ((translateCenter * cube->center) * -1);
            glNormal3f(square_normal.x, square_normal.y, square_normal.z);
            glVertex3f(v.x, v.y, v.z);
//            qDebug() << i;
        }
        glEnd();
    }

}



void OpenGLWidget::draw3DLine(QVector3D v0, QVector3D v1)
{
    glBegin(GL_LINE_STRIP);
    glVertex3f(v0.x(), v0.y(), v0.z());
    glVertex3f(v1.x(), v1.y(), v1.z());
    glEnd();
}

void OpenGLWidget::draw3DLine(Vector3 v0, Vector3 v1)
{
    draw3DLine(QVector3D(v0.x, v0.y, v0.z), QVector3D(v1.x, v1.y, v1.z));
}

void OpenGLWidget::drawTriangle(Triangle3 triangle)
{
    glBegin(GL_TRIANGLE_STRIP);
    Vector3 normal = triangle.normal();

    Vector3 splinePoint(triangle.x.splinePoint);
    splinePoint = scaleMatrix * splinePoint;
    normal = (triangle.x + (splinePoint * -1)).normalize();
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(triangle.x.x, triangle.x.y, triangle.x.z);

    splinePoint = Vector3(triangle.y.splinePoint);
    splinePoint = scaleMatrix * splinePoint;
    normal = (triangle.y + (splinePoint * -1)).normalize();
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(triangle.y.x, triangle.y.y, triangle.y.z);

    splinePoint = Vector3(triangle.z.splinePoint);
    splinePoint = scaleMatrix * splinePoint;
    normal = (triangle.z + (splinePoint * -1)).normalize();
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(triangle.z.x, triangle.z.y, triangle.z.z);
    glEnd();



}

void OpenGLWidget::drawAxis()
{
    if (!isAxisVisible)
    {
        return;
    }
    glColor3f(1.0, 0, 0);
    QVector3D zero = QVector3D(0,0,0);
    zero.setX(-AXIS_LENGTH);
    draw3DLine(zero, QVector3D(AXIS_LENGTH, 0, 0));
    zero.setX(0);
    zero.setY(-AXIS_LENGTH);
    glColor3f(0, 1.0, 0);
    draw3DLine(zero, QVector3D(0, AXIS_LENGTH, 0));
    zero.setY(0);
    zero.setZ(-AXIS_LENGTH);
    glColor3f(0, 0, 1.0);
    draw3DLine(zero, QVector3D(0,0, AXIS_LENGTH));
}

void OpenGLWidget::drawGrid()
{
    if (!isGridXZVisible && !isGridXYVisible && !isGridYZVisible)
    {
        return;
    }

    if (isGridXZVisible || isGridXYVisible)
    {
        glColor3f(1.0, 0, 0);
        draw3DLine(QVector3D(-GRID_SIZE,0,0), QVector3D(-AXIS_LENGTH, 0, 0));
        draw3DLine(QVector3D(GRID_SIZE,0,0), QVector3D(AXIS_LENGTH, 0, 0));

    }
    if (isGridXYVisible || isGridYZVisible)
    {
        glColor3f(0, 1.0, 0);
        draw3DLine(QVector3D(0,-GRID_SIZE,0), QVector3D(0, -AXIS_LENGTH, 0));
        draw3DLine(QVector3D(0,GRID_SIZE,0), QVector3D(0, AXIS_LENGTH, 0));
    }
    if (isGridXZVisible || isGridYZVisible)
    {
        glColor3f(0, 0, 1.0);
        draw3DLine(QVector3D(0,0,-GRID_SIZE), QVector3D(0, 0, -AXIS_LENGTH));
        draw3DLine(QVector3D(0,0,GRID_SIZE), QVector3D(0, 0, AXIS_LENGTH));
    }

    for (int i = 5; i < GRID_SIZE; i+=5)
    {

        if (isGridXZVisible)
        {
            glColor3f(1.0, 0.5, 0.5);
            draw3DLine(QVector3D(-GRID_SIZE, 0, i), QVector3D(GRID_SIZE,0,i));
            draw3DLine(QVector3D(-GRID_SIZE, 0, -i), QVector3D(GRID_SIZE, 0, -i));

            draw3DLine(QVector3D(i, 0, -GRID_SIZE), QVector3D(i, 0, GRID_SIZE));
            draw3DLine(QVector3D(-i, 0, -GRID_SIZE), QVector3D(-i, 0, GRID_SIZE));
        }
        if (isGridXYVisible)
        {
            glColor3f(0.5, 1.0, 0.5);
            draw3DLine(QVector3D(i, -GRID_SIZE, 0), QVector3D(i, GRID_SIZE, 0));
            draw3DLine(QVector3D(-i, -GRID_SIZE, 0), QVector3D(-i, GRID_SIZE, 0));

            draw3DLine(QVector3D(-GRID_SIZE, i, 0), QVector3D(GRID_SIZE,i,0));
            draw3DLine(QVector3D(-GRID_SIZE, -i, 0), QVector3D(GRID_SIZE, -i, 0));
        }
        if (isGridYZVisible)
        {
            glColor3f(1.0, 1.0, 0);
            draw3DLine(QVector3D(0, -GRID_SIZE, i), QVector3D(0, GRID_SIZE, i));
            draw3DLine(QVector3D(0, -GRID_SIZE, -i), QVector3D(0, GRID_SIZE, -i));

            draw3DLine(QVector3D(0, i, -GRID_SIZE), QVector3D(0, i, GRID_SIZE));
            draw3DLine(QVector3D(0, -i, -GRID_SIZE), QVector3D(0, -i, GRID_SIZE));
        }
    }
}

void OpenGLWidget::setLighting()
{
    Vector3 v;
    for (QVector<LightSource>::iterator it = dataManager->lights.begin(); it != dataManager->lights.end(); it++)
    {
        glEnable(it->lightNumber);
        GLfloat ambient[] = {it->ambient.x, it->ambient.y, it->ambient.z, it->ambient.w};
        glLightfv(it->lightNumber, GL_AMBIENT, ambient);

        GLfloat diffuse[] = {it->diffuse.x, it->diffuse.y, it->diffuse.z, it->diffuse.w};
        glLightfv(it->lightNumber, GL_DIFFUSE, diffuse);

        GLfloat specular[] = {it->specular.x, it->specular.y, it->specular.z, it->specular.w};
        glLightfv(it->lightNumber, GL_SPECULAR, specular);

        v = scaleMatrix * Vector3(it->position);
        GLfloat pos[] = {v.x, v.y, v.z};
        glLightfv(it->lightNumber, GL_POSITION, pos);
    }
}

void OpenGLWidget::lookPrevPoint()
{
    if (dataManager->points.size() == 0)
        return;

    currentViewedPoint = (currentViewedPoint - 1) % (dataManager->points.size() + 1);
    if (currentViewedPoint < 0)
    {
        currentViewedPoint = dataManager->points.size();
    }
    if (currentViewedPoint == 0)
    {
        viewTo.x = viewTo.y = viewTo.z = 0;
    } else {
        Vector3 v = Vector3(*(dataManager->points[currentViewedPoint - 1]));
        viewTo.x += v.x;
        viewTo.y += v.y;
        viewTo.z += v.z;
        viewTo = scaleMatrix * viewTo;
    }
}

void OpenGLWidget::lookNextPoint()
{
    if (dataManager->points.size() == 0)
        return;

    currentViewedPoint = (currentViewedPoint + 1) % (dataManager->points.size() + 1);
    if (currentViewedPoint == 0)
    {
        viewTo.x = viewTo.y = viewTo.z = 0;
    } else {
        Vector3 v = Vector3(*(dataManager->points[currentViewedPoint - 1]));
        viewTo.x += v.x;
        viewTo.y += v.y;
        viewTo.z += v.z;
        viewTo = scaleMatrix * viewTo;
    }
}

void OpenGLWidget::addLight()
{
    if (dataManager->lights.size() >= 8)
        return;
    qDebug() << dataManager->lights.size();
    LightSource light;
    light.lightNumber = lights[dataManager->lights.size()];
    light.ambient = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
    light.diffuse = Vector4(0.8f, 0.8f, 0.8, 1.0f);
    light.specular = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    light.position = QVector3D(250, 250, 5);
    dataManager->lights.push_back(light);
}

void OpenGLWidget::clear()
{
    dataManager->points.clear();
}

void OpenGLWidget::hideAxis()
{
    isAxisVisible = !isAxisVisible;
}

void OpenGLWidget::hideGrid()
{
    isGridXYVisible = isGridYZVisible = isGridXZVisible = (!isGridXYVisible && !isGridXZVisible && !isGridYZVisible);
}

void OpenGLWidget::hideGridXY()
{
    isGridXYVisible = !isGridXYVisible;
}

void OpenGLWidget::hideGridXZ()
{
    isGridXZVisible = !isGridXZVisible;
}

void OpenGLWidget::hideGridYZ()
{
    isGridYZVisible = !isGridYZVisible;
}

void OpenGLWidget::hidePointLines()
{
    isPointLinesVisible = !isPointLinesVisible;
}

void OpenGLWidget::hidePoints()
{
    isPointsVisible = !isPointsVisible;
}

void OpenGLWidget::hideSpline()
{
    isSplineVisible = !isSplineVisible;
}

void OpenGLWidget::drawCylinder()
{
    struct f_frame f = dataManager->calculateFrame(shape, cylinder_radius);
    cylinderList = f.cylinderList;
    crossSectionList = f.crossSectionList;
    currentCrossSection = NULL;
    lids = f.lids;
    cubeFrame = 0;
    //    splinePoints = dataManager->calculateCatmullRom();
//    cubeFrame = 0;
}

void OpenGLWidget::toggleSpecial(bool on)
{
    special = on;
}
