#include "basicopenglview.h"

BasicOpenGLView::BasicOpenGLView(QWidget *parent)
      : QGLWidget(parent)
{
    objectManager = new ObjectManager();
    pressed_point = NULL;
    selectedPolygon = NULL;
    oldPolygon = NULL;
}

void BasicOpenGLView::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glShadeModel( GL_FLAT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPointSize(5);
}

void BasicOpenGLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,GLdouble(width),0,GLdouble(height),-10.0,10.0);
   // glOrtho(-(GLdouble)width/2.0, (GLdouble)width/2.0, -(GLdouble)height/2.0, (GLdouble)height/2.0, -10.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    qDebug()<< "resize\n";
}

void BasicOpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f);
    drawScreen();
}

/**
 * @brief BasicOpenGLView::mousePressEvent
 *      The mouse press is only used to determine of a user has selected either a polygon or a point of the polygon
 *      This will be used to moving that point of polygon elsewhere.
 * @param event
 */
void BasicOpenGLView::mousePressEvent(QMouseEvent *event)
{
    Vector2 point(mStack.get_product().inverse() * Vector2(event->x(), height() - event->y()));
    pointTracker = point;
    selectedPolygon = objectManager->polygonExists(point);
    pressed_point = objectManager->pointExists(&point);

    // Check if the pressed_point is associated with a polygon
    if (objectManager->polygonPoint != NULL)
    {
        selectedPolygon = objectManager->polygonPoint;
    }
    update();
}

/**
 * @brief BasicOpenGLView::mouseMoveEvent
 *      If either the pressed_point or the selectedPolygon variables is set, start moving those points around
 *      Pressing a point takes precedence over moving a polygon
 * @param event
 */
void BasicOpenGLView::mouseMoveEvent(QMouseEvent *event)
{
    if (pressed_point != NULL)
    {
        pressed_point->x = event->x();
        pressed_point->y = height() - event->y();
        *pressed_point = mStack.get_product().inverse() * *pressed_point;
    } else if (selectedPolygon != NULL)
    {
        // Take the difference between the points, and move the point by that difference
        Vector2 eventVector(mStack.get_product().inverse() * Vector2(event->x(), height() - event->y()));
        double x_diff = eventVector.x - pointTracker.x;
        double y_diff = eventVector.y - pointTracker.y;
        // Move every point in the polygon by the difference
        for (std::vector<Vector2 *>::iterator it = selectedPolygon->points.begin(); it != selectedPolygon->points.end(); it++)
        {
            (*it)->x += x_diff;
            (*it)->y += y_diff;
        }
        pointTracker = eventVector;
    }


    update();
}

/**
 * @brief BasicOpenGLView::mouseReleaseEvent
 *      Various actions happen on mouse release. If a polygon is selected, do not attempt to create polygons or add new points.
 *      If the old polygon is set, that means we are deselecting the current polygon.
 *      If we can create a polygon, add the screenPoints to a new Polygon object, and add it to the object manager. Then, clear the screenPoints
 *      If the pressed_point is set, set it to NULL. This ensures no point is selected
 *      Check if a point exists. If there is no point there, create a point
 * @param event
 */
void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *event)
{
    Vector2 * point = new Vector2(mStack.get_product().inverse() * Vector2(event->x(), height() - event->y()));

    if (selectedPolygon != NULL)
    {
        pressed_point = NULL;
        oldPolygon = selectedPolygon;
    } else if (oldPolygon != NULL)
    {
        oldPolygon = NULL;
    }
    else if (objectManager->canCreatePolygon(point))
    {
        free(point);
        objectManager->polygons.push_back(new Polygon(objectManager->screenPoints));
        objectManager->screenPoints.clear();
    } else if (pressed_point != NULL)
    {
        pressed_point = NULL;
    }
    else if (objectManager->pointExists(point) == NULL)
    {
        objectManager->addPoint(point);
    } else {
        free(point);
    }
    update();
}


void BasicOpenGLView::translate(double x, double y)
{
    mStack.push(linalg::translate2(x,y));
    update();
}

void BasicOpenGLView::rotate(double angle)
{
    mStack.push(linalg::rotate2(angle));
    update();
}

void BasicOpenGLView::scale(double x, double y)
{
    mStack.push(linalg::scale2(x, y));
    update();
}

void BasicOpenGLView::undo()
{
    mStack.pop();
    update();
}

void BasicOpenGLView::applyMatrix(double m[][3])
{
    mStack.push(new Matrix33(m));
    update();
}

void BasicOpenGLView::drawScreen()
{
    stackViewer->setText(mStack.toString());
    drawPolygons();
    drawPoints(objectManager->screenPoints, false);
}

void BasicOpenGLView::drawPolygons()
{
    for (std::vector<Polygon *>::iterator it = objectManager->polygons.begin(); it != objectManager->polygons.end(); it++)
    {
        drawPoints((*it)->points, true);
        fillPolygon((*it)->points, false);
    }

    // Highlight the selected polygon
    if (selectedPolygon != NULL)
    {
        fillPolygon(selectedPolygon->points, true);
    }
}

void BasicOpenGLView::drawCircle(double radius, double xcen, double ycen, bool line)
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

// The drawing takes into account the matrix stack to ensure we draw all
// points in the proper.
void BasicOpenGLView::drawPoints(std::vector<Vector2 *> points, bool isPolygon)
{
    // Last point holds a reference to the previous point, to be able to draw lines between points
    Vector2 * lastPoint = NULL;
    Vector2 actualPoint;
    for (std::vector<Vector2 *>::iterator it = points.begin(); it != points.end(); it++)
    {
        // Transform all points by the matrix in the stack to draw them in the proper place on the screen
        actualPoint = mStack.get_product() * (*(*it));
        drawCircle((double)RADIUS, actualPoint.x, actualPoint.y, false);
        if (lastPoint != NULL)
        {
            drawLine(actualPoint, *lastPoint);
            lastPoint->x = actualPoint.x;
            lastPoint->y = actualPoint.y;
        } else {
            lastPoint = new Vector2(actualPoint.x, actualPoint.y);
        }
    }

    // If it is a polygon, draw a line from the first and last point
    if (isPolygon)
    {
        drawLine(mStack.get_product() * (*points.front()), actualPoint);
    }
    free(lastPoint);
}

void BasicOpenGLView::drawLine(Vector2 v0, Vector2 v1)
{
    glBegin(GL_LINES);
    glVertex2f(v0.x, v0.y);
    glVertex2f(v1.x, v1.y);
    glEnd();
}

void BasicOpenGLView::fillPolygon(std::vector<Vector2 *> points, bool highlight)
{
    glBegin(GL_POLYGON);
    if (highlight)
    {
        glColor3f(1.0f, 1.0f, 0);
    }
    Vector2 v;
    for (std::vector<Vector2 *>::iterator it = points.begin(); it != points.end(); it++)
    {
        v = mStack.get_product() * *(*it);
        glVertex2f(v.x, v.y);
    }
    if (highlight)
    {
        glColor3f(0.0f, 0.0f, 1.0f);
    }
    glEnd();
}
