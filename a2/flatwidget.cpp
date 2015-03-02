#include "flatwidget.h"

FlatWidget::FlatWidget(DataManager * d) : OpenGLWidget(d)
{
    pressedPoint = NULL;
}

void FlatWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel( GL_FLAT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPointSize(5);
}

void FlatWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f);
    drawAxis();
    draw();
}

void FlatWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width,GLdouble(width),-height,GLdouble(height),-10.0,10.0);

    glMatrixMode(GL_MODELVIEW);
}

void FlatWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (pressedPoint != NULL)
    {
        pressedPoint = NULL;
    } else
    {
        QVector3D * point = new QVector3D(get3DPoint( processMouse(QVector2D(e->x(), height() - e->y()))));
        dataManager->addPoint(point);
    }
    update();
}

void FlatWidget::mousePressEvent(QMouseEvent *e)
{
    QVector3D mousePoint = get3DPoint( processMouse(QVector2D(e->x(), height() - e->y())));
    pressedPoint = pointAt(mousePoint);
}

// Only fired if mouse is pressed, ensured by QT
void FlatWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (pressedPoint != NULL)
    {
        modifyPoint(pressedPoint, processMouse(QVector2D(e->x(), height() - e->y())));
    }
    update();
}

void FlatWidget::drawCircle(double radius, double xcen, double ycen, bool line)
{
   GLint i;
   static GLfloat circcoords[100][2];

   for(i=0;i<100;i++) {
     circcoords[i][0]=radius*cos(i*2*M_PI/100.0)+xcen;
     circcoords[i][1]=radius*sin(i*2*M_PI/100.0)+ycen;
   }

   if (line)   glBegin(GL_LINES); else glBegin(GL_POLYGON);
      for(i=0;i<100;i++)
         glVertex2fv(&circcoords[i][0]);
   glEnd();
}

void FlatWidget::drawLine(QVector2D v0, QVector2D v1)
{
    glBegin(GL_LINES);
    glVertex2f(v0.x(), v0.y());
    glVertex2f(v1.x(), v1.y());
    glEnd();
}

void FlatWidget::draw()
{
    glColor3f(0.7, 0.0, 1.0);
    QVector2D point;
    QVector2D prevPoint;
    Vector2 v;
    bool firstPoint = true;
    for (QVector<QVector3D *>::iterator it = dataManager->points.begin(); it != dataManager->points.end(); it++)
    {
        point = get2DPoint(*(*it));
        drawCircle((double)RADIUS, point.x(), point.y(), false);
        if (!firstPoint)
        {
            drawLine(point, prevPoint);
        } else {
            firstPoint = false;
        }
        prevPoint = point;
    }

    glColor3f(0.0, 1.0, 1.0);
    Vector3 catmullVector;
    Vector3 prevCatmull;
    firstPoint = true;
    QVector<Vector3> catmullList = dataManager->calculateCatmullRom();
    for (QVector<Vector3>::iterator it = catmullList.begin(); it != catmullList.end(); it++)
    {
        catmullVector = *it;
        if (!firstPoint)
        {
            drawLine(get2DPoint(QVector3D(catmullVector.x, catmullVector.y, catmullVector.z)), get2DPoint(QVector3D(prevCatmull.x, prevCatmull.y, prevCatmull.z)));
        } else {
            firstPoint = false;
        }
        prevCatmull = catmullVector;
    }
}

void FlatWidget::drawAxis()
{
    glColor3f(1.0,1.0,1.0);
    QVector2D zero = QVector2D(0,0);
    zero.setX(-FLAT_AXIS_LENGTH);
    drawLine(zero, QVector2D(FLAT_AXIS_LENGTH, 0));
    zero.setX(0);
    zero.setY(-FLAT_AXIS_LENGTH);
    drawLine(zero, QVector2D(0, FLAT_AXIS_LENGTH));
}

QVector2D FlatWidget::processMouse(QVector2D mouse)
{
    mouse.setX((mouse.x() * 2) - width());
    mouse.setY((mouse.y() * 2) - height());
    return mouse;
}

QVector3D * FlatWidget::pointAt(QVector3D point)
{
    for (QVector<QVector3D *>::iterator it = dataManager->points.begin(); it != dataManager->points.end(); it++)
    {
        if (pointOnCircle(get2DPoint(point), get2DPoint( *(*it) ), (double)RADIUS))
        {
            return *it;
        }
    }
    return NULL;
}

bool FlatWidget::pointOnCircle(QVector2D point, QVector2D circle, double radius)
{
    return pow((point.x() - circle.x()), 2) + pow((point.y() - circle.y()), 2) <= pow(radius, 2);
}
