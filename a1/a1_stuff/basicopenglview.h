#ifndef BASICOPENGLVIEW_H
#define BASICOPENGLVIEW_H

#include <QGLWidget>
#include <math.h>
#include <QtDebug>
#include <QMouseEvent>
#include <QTextEdit>
#include "objectmanager.h"

/**
  * @class  BasicOpenGLView
  * @brief  our OpenGL view derived from QGLWidget.
  * We have to override several functions for our
  * application-specific OpenGL drawing functionality
  */
class BasicOpenGLView : public QGLWidget
{
    /**
      * macro needed to be inserted in every QT derived class.
      */
    Q_OBJECT
public:

    /**
      * our constructor
      * @param  parent the parent object of the widget.
                pass this one on to the superclass constructor
      */
    explicit BasicOpenGLView(QWidget *parent = 0);

    /**
     * @brief drawPoints: Takes in a vector of Vector2 pointers, and draws those points to the screen.
     *    If isPolygon is true, then it will fill in the polygon.
     * @param points: A vector of Vector2 pointers to draw to the screen
     * @param isPolygon: A boolean telling the function if it's a finished polygon or not.
     */
    void drawPoints(std::vector<Vector2 *> points, bool isPolygon);

    /**
     * @brief drawCircle: Draws a point on the screen as a circle at point xcen, ycen with
     *  a fixed radius.
     * @param radius: The radius of the circle being drawn.
     * @param xcen: The x coordinate of the centre of the circle
     * @param ycen: The y coordinate of the centre of the circle
     * @param line
     */
    void drawCircle(double radius, double xcen, double ycen, bool line);

    /**
     * @brief drawScreen: Draws all points and polygons to the screen in their
     *  proper location
     */
    void drawScreen();

    /**
     * @brief drawLine: Draws a line between two given vertices
     * @param v0: The first vertex to start the line from
     * @param v1: The second vertex to end the line at
     */
    void drawLine(Vector2 v0, Vector2 v1);

    /**
     * @brief drawPolygons: Draws the Polygons stored in the ObjectManager to the screen. All
     *      finished polygons are stored in the ObjectManager. This function will draw the circles, lines,
     *      and fill in the polygon.
     */
    void drawPolygons();

    /**
     * @brief fillPolygon: Fills in a polygon the specific colour given a list of points. If highlight is true, it will
     *      colour the polygon yellow.
     * @param points: The vertices of the polygon to be filled in
     * @param highlight: A boolean determining if the polygon should be colour highlighted
     */
    void fillPolygon(std::vector<Vector2 *> points, bool highlight);

    /**
     * @brief setStackViewer: A setter function to give the BasicOpenGLView a reference to
     *      the QTextEdit object that displays the list.
     * @param e: The QTextEdit reference representing the stack displayer
     */
    void setStackViewer(QTextEdit * e) {stackViewer = e;}

signals:

public slots:
    /**
     * @brief translate: Invoked when the user clicks the 'translate' button in the UI. It
     *      will create a translation matrix using the x and y parameters, and then push
     *      the matrix to the stack.
     * @param x: The x value to translate by
     * @param y: The y value to translate by
     */
    void translate(double x, double y);

    /**
     * @brief rotate: Invoked when the user clicks the rotate button. Will create a
     *      rotation matrix using the angle in degrees, and then push the matrix to the
     *      stack.
     * @param angle: The angle in degrees to rotate by
     */
    void rotate(double angle);

    /**
     * @brief scale: Invoked when the user clicks the 'scale' button. Will create a
     *      scale matrix using the x and y parameters, and then push the matrix to the stack.
     * @param x: The x value to scale by
     * @param y: The y value to scale by
     */
    void scale(double x, double y);

    /**
     * @brief undo: Invoked when the user clicks the 'undo' button. Reverts the previous
     *      transformation applied to the polygons and points. It simply pops the
     *      previous matrix from the stack. If no matrices on the stack, do nothing.
     */
    void undo();

    /**
     * @brief applyMatrix: Invoked when the user clicks the 'Apply Matrix' button. Will take the
     *      3x3 array m, and create a matrix from it. It will then push it on the stack.
     * @param m: The 3x3 array representing the matrix to create.
     */
    void applyMatrix(double m[][3]);

protected:

    /**
      * function called automatically by QT after the OpenGL context is created
      * in here, do all OpenGL setup stuff, that you can before the actual program
      * execution starts
      */
    void initializeGL();

    /**
      * the function called whenever our Widget is being redrawn.
      * assume that the BasicOpenGLView's OpenGL context has already
      * been made the current one, so no need to call
      * this->makeCurrent(); anymore
      * Do all your rendering loop related code in there
      */
    void paintGL();

    /**
      * method called when the widget is resized.
      * we need code in there, to react to the changed window size
      * otherwise the rendering will look skewed and ugly
      */
    void resizeGL(int width, int height);

    /**
      * function called when a mouse button is pressed and the cursor is hovering
      * over our widget
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mousePressEvent(QMouseEvent *event);

    /**
      * function called when mouse cursor is moved inside our widgets region
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief mouseReleaseEvent
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

private:
    /**
     * @brief stackViewer A reference to the QTextEdit object to output the stack contents to screen
     */
    QTextEdit * stackViewer;

    /**
     * @brief pressed_point If the user pressed down on a point, this becomes a reference to that point.
     *      Else, it is null.
     */
    Vector2 * pressed_point;

    /**
     * @brief objectManager A class holding references and functionality related to the objects on the screen. All points, polygons,
     *      and methods that manipulate or access those objects on the screen reside in the object manager.
     */
    ObjectManager * objectManager;

    /**
     * @brief mStack The stack of matrices representing the transforms applied to the objects on the screen.
     */
    MatrixStack mStack;

    /**
     * @brief selectedPolygon A pointer to the currently selected polygon. Null if no polygon is selected.
     */
    Polygon * selectedPolygon;

    /**
     * @brief oldPolygon A pointer to the last polygon selected. Used to determine if the user has clicked away from
     *      a polygon without immediately creating a new point to screen. Creates a state in which the user can click away from a polygon to deselect.
     */
    Polygon * oldPolygon;

    /**
     * @brief pointTracker Records the first place the user pressed down. Allows us to take the difference from this point to the
     *      moved position to allow us to move a whole polygon around on the screen.
     */
    Vector2 pointTracker;

};

#endif // BASICOPENGLVIEW_H
