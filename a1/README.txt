JUSTIN GUZE
V00723799

USER GUIDE

1. INTRODUCTION
This guide will walk the user through all the functions of the application and the inner structures used in the application

2. CREATING POLYGONS AND POINTS
Points can be created at will by simply clicking anywhere on the screen. Subsequent  will create new points connected to the
previous point created. Click and hold any point to drag it and move it to a different location.

To create a polygon, you must have first placed 3 points. Then, at any time, click on the first point created to create
a polygon. After this, new clicks will place a new point on the screen to start creating new polygons. The points on the
polygon can continue to be manipulated to move the points around the screen.

Click on any polygon to highlight it. Click and drag the polygon to move it around the screen.

3. TRANSFORMATIONS
There are various functions on the right side of the screen. From top to bottom, they will allow the user to transform the points
and polygons on the screen. All objects are transformed by the product of all transformation matrices on the stack. The 
stack contents can be viewed as viewable in the field above the 'STACK' label. 

3.1 TRANSLATION
To translate all points and polygons on the screen, fill out the x and y value above the 'translate' button.
The 'x' field will translate all objects on the screen by the x value. The 'y' field will translate
all objects on the screen by the y value. Clicking 'translate' will invoke the translate function, and
add a translation matrix to the stack with the x and y translation fields.

3.2 ROTATION
To rotate all objects on the screen, enter an angle in degrees into the angle field. Hitting the 'rotate' button
will add a rotation matrix to the stack with the angle entered, and rotate all objects on the field around the 0,0 point.

3.3 SCALE
To scale all objects on the screen around the 0,0 point, enter in the x scale and the y scale values in their respective fields.
Then, click the 'scale' button to create a scale matrix and push it onto the stack.

3.4 CUSTOM MATRIX
To push a custom 3x3 matrix onto the stack, simply fill out all the entries into the 9 fields above the 'Push Matrix'
button. Pressing the 'Push Matrix' button will push the matrix onto the stack if all the fields are valid.

3.5 POP MATRIX
Pressing the 'Pop Matrix' button will pop the last matrix pushed onto the stack and undo the previous transformation.

4. STRUCTURE
The code is built upon the existing BasicOpenGLWidget provided in class. An ObjectManager class was added
to manage all points and polygons on the screen as std::vector objects. The ObjectManager will manage
access to these objects, and provide methods to manipulate these objects.

A custom linear algebra library was created. It has classes for vectors (Vector2, Vector3) and
matrices (Matrix22, Matrix33). This library contains functions to calculate the determinant, cofactor, adjoint,
inverse of matrices, and can also handle the multiplication of matrices, vectors, etc. It contains a multitude of
functions documented under 'linearalg.h'

To manage all matrices, a custom stack called MatrixStack was created. This will push any Matrix33 to the stack,
and also keeps a reference to the product of all matrices on the stack. Every push operation multiplies the pushed
matrix with the product, and every pop will compute the inverse of the popped matrix, and multiply it by the product.

On draw, every point is multiplied by the current product of the matrix stack, and each point, line, and filled polygon
is drawn at the position. The actual position of the points remains the same in memory. To fix the mouse clicks, each mouse click
is multiplied by the inverse of the stack product to allow it to work.
