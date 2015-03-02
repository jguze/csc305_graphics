#ifndef FLATWIDGET_H
#define FLATWIDGET_H

#include <QMouseEvent>
#include "openGLWidget.h"

#define FLAT_AXIS_LENGTH 1000 // The length of the axis for the flat 2D views

/**
 * @brief The FlatWidget class The 2D version of the OpenGLWidget class. It still represents all
 * points in the dataManager to the screen, but only on one plane depending on the implementation.
 * This class is must be inherited by other classes that will specify what sort of plane the 2D
 * view is looking at for 3D points
 */
class FlatWidget : public OpenGLWidget
{
    Q_OBJECT
public:
    /**
     * @brief FlatWidget The constructor for the flat widget. Takes in a dataManager to record and draw the 3D points to the 2D view
     * @param d
     */
    FlatWidget(DataManager * d);

    /**
     * @brief draw The basic draw function that will draw everything to the screen.
     */
    void draw();

    /**
     * @brief drawCircle Draws a 2D circle on the screen given a radius, xcentre, ycentre. A boolean line
     * checks if the circle should be filled in or not
     * @param radius The radius of the circle
     * @param xcen The x centre point of the circle
     * @param ycen The y centre point of the circle
     * @param line If true, do not fill in the circle, otherwise fill in the circle
     */
    void drawCircle(double radius, double xcen, double ycen, bool line);

    /**
     * @brief drawLine Given two 2D points, it will draw a line between the two on the screen
     * @param v0 The starting point of the line
     * @param v1 The ending point of the line
     */
    void drawLine(QVector2D v0, QVector2D v1);

    /**
     * @brief drawAxis Draws the plane's axis to the screen, depending on which plane the view is
     * representing from the 3D points.
     */
    void drawAxis();

    void drawCylinder();
    void toggleSpecial(bool on);
protected:
    /**
     * @brief initializeGL Initializes the view to be a 2D view, where point 0,0 lies in the middle of the screen
     */
    void initializeGL();

    /**
     * @brief resizeGL Resizes the view to look appropriate regardless of window size
     * @param w The new width of the widget
     * @param h The new height of the widget
     */
    void resizeGL(int w, int h);

    /**
     * @brief paintGL Updates the widget to draw everything to the screen. Draws the axis first, then the points, then the spline
     */
    void paintGL();

    /**
     * @brief mouseReleaseEvent On mouse release, the view will either place a point on the screen and record it in the dataManager,
     * or move a point around on the screen.
     * @param e
     */
    void mouseReleaseEvent(QMouseEvent *e);

    /**
     * @brief mousePressEvent Checks to see if the user is clicking on a point. If so, do not place a point and move that point instead
     * @param e
     */
    void mousePressEvent(QMouseEvent *e);

    /**
     * @brief mouseMoveEvent Called when the mouse is moving and pressed. If a point was pressed, move that point around
     */
    void mouseMoveEvent(QMouseEvent *);

    /**
     * @brief pointOnCircle Checks if a point is within a circle given the radius.
     * @param point The point to check if lying in the circle
     * @param circle The centre point of the circle
     * @param radius The radius of the circle
     * @return True if the point lies in the circle, false otherwise
     */
    bool pointOnCircle(QVector2D point, QVector2D circle, double radius);

    /**
     * @brief pointAt Checks to see if there is a point at the point given.
     * @param point A 3D point to check if it may lie on the 2D plane
     * @return A reference to the 3D point if there is a point at that location, NULL otherwise
     */
    QVector3D * pointAt(QVector3D point);

    /**
     * @brief get2DPoint A pure virtual method that will give the plane's 2D points given a 3D point from memory.
     * @param point The 3D point to draw to the 2D plane
     * @return The appropriate 2D point given the plane
     */
    virtual QVector2D get2DPoint(QVector3D point) = 0;

    /**
     * @brief get3DPoint A pure virtual method that will give a 3D point given a 2D location pressed on the 2D plane
     * @param point The 2D point clicked on the widget
     * @return A 3D point representing that point on the plane
     */
    virtual QVector3D get3DPoint(QVector2D point) = 0;

    /**
     * @brief modifyPoint Moves the 3D point given a new 2D location, which depends on the plane being viewed
     * @param point A reference to the 3D point being modified
     * @param p The point where the point will be moved to
     */
    virtual void modifyPoint(QVector3D * point, QVector2D p) = 0;

    /**
     * @brief processMouse Transforms the mouse click taken from QT to adhere to a modified OpenGL
     * coordinate system.
     * @param mouse The mouse point to be modified.
     * @return A 2D point representing the proper mouse coordinates given the widget's coordinate system
     */
    QVector2D processMouse(QVector2D mouse);

    /**
     * @brief pressedPoint A reference to a point if a point was pressed. NULL otherwise
     */
    QVector3D * pressedPoint;
};

#endif // FLATWIDGET_H
