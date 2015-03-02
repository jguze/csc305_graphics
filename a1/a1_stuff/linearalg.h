#ifndef LINEARALG_H
#define LINEARALG_H

#include <math.h>
#include <QStack>
#include <QtDebug>
#include <sstream>

#define PI 3.14159265
#define EPSILON 0.001f

class Polygon;
class Vector2;
class Vector3;
class Matrix22;
class Matrix33;

/**
 *  A collection of only functions to perform various linear algebra operations
 */
namespace linalg
{
    /**
     * @brief determinant22 Takes the determinant of a given 2x2 matrix.
     * @param m The matrix to find the determinant of
     * @return A double representing the determinant of m
     */
    double determinant22(Matrix22 m);

    /**
     * @brief determinant33 Finds the determinant of a given 3x3 matrix
     * @param m A 3x3 matrix to find the determinant of
     * @return A double representing the determinant
     */
    double determinant33(Matrix33 m);

    /**
     * @brief cofactor33 Finds the cofactor matrix of a 3x3 matrix.
     * @param m The 3x3 matrix to find the cofactor of
     * @return A 3x3 matrix representing the cofactor matrix of m
     */
    Matrix33 cofactor33(Matrix33 m);

    /**
     * @brief transpose33 Transposes a given 3x3 matrix
     * @param m The 3x3 matrix to transpose
     * @return The transposed 3x3 matrix
     */
    Matrix33 transpose33(Matrix33 m);

    /**
     * @brief adjoint33 Takes the adjoint of a given 3x3 matrix. The adjoint of A is performed by the formula adjoint(A) = cofactor(A)^T
     * @param m The matrix to perform the adjoint on
     * @return The adjointed 3x3 matrix
     */
    Matrix33 adjoint33(Matrix33 m);

    /**
     * @brief inverse33 Performs the inverse on a given 3x3 matrix by using the formula A^-1 = 1/det(A) * adjoint(A)
     * @param m The matrix to invert
     * @return The inverted 3x3 matrix
     */
    Matrix33 inverse33(Matrix33 m);

    /**
     * @brief translate2 Creates a translation matrix to perform in 2d, and returns the homogenous 3x3 matrix
     * @param v A vector representing the x and y to translate by
     * @return A 3x3 matrix to do the 2d translation
     */
    Matrix33 * translate2(Vector2 v);

    /**
     * @brief translate2 Creates a translation matrix to perform in 2d, and returns the homogenous 3x3 matrix.
     * @param x The x value to translate by
     * @param y The y value to translate by
     * @return A 3x3 matrix to do the 2d translation
     */
    Matrix33 * translate2(double x, double y);

    /**
     * @brief rotate2 Creates a rotation matrix for 2d coordinates, and returns the homogenous 3x3 matrix.
     * @param angle The angle in degrees to create the rotation matrix with
     * @return A 3x3 matrix to do the 2d rotation
     */
    Matrix33 * rotate2(double angle);

    /**
     * @brief scale2 Creates a scale matrix for 2d coordinates, and returns the homogenous 3x3 matrix
     * @param x The x value to scale by
     * @param y The y value to scale by
     * @return A 3x3 matrix to do the 2d scale
     */
    Matrix33 * scale2(double x, double y);

    /**
     * @brief scale2 Creates a scale matrix for 2d coordinates, and returns the homogenous 3x3 matrix
     * @param v A vector representing the x and y to scale by
     * @return A 3x3 matrix to do the 2d scale
     */
    Matrix33 * scale2(Vector2 v);

    /**
     * @brief distance Computes the distance between two points
     * @param a The first point
     * @param b The second point
     * @return A double of the distance between the two points
     */
    double distance(Vector2 a, Vector2 b);

    /**
     * @brief crossProduct Takes the cross product of two points a and b as 'a x b'
     * @param a The first point
     * @param b The second point
     * @return The cross product of a x b
     */
    double crossProduct(Vector2 a, Vector2 b);

    /**
     * @brief linesIntersect Determines if two lines intersect with each other. Each line a and b are represented by two points
     * @param a1 The start of line a
     * @param a2 The end of line a
     * @param b1 The start of line b
     * @param b2 The end of line b
     * @return True if the lines intersect, false otherwise
     */
    bool linesIntersect(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2);

    /**
     * @brief raycastAlgorithm Performs the raycast algorithm to determine if a point is inside a polygon.
     *      This is done by drawing a line from the y axis to point v, and determining how many lines it
     *      intersects in polygon p. If the number of intersections is odd, the point lies in the polygon.
     * @param v The point to check if it resides in a polygon
     * @param p The polygon to determine if the point exists within it
     * @return True if the point lies in the polygon, false otherwise
     */
    bool raycastAlgorithm(Vector2 v, Polygon p);

    /**
     * @brief pointOnLine Determines if a point rests on some line l, defined by two points This is
     *      done by checking if distance between the point and the start of the line, and the point and the
     *      end of the line is equal to the size of the line.
     * @param point The point to determine if it exists on the line
     * @param l1 The start of the line l
     * @param l2 The end of the line l
     * @return True if the point lies on line l, false otherwise
     */
    bool pointOnLine(Vector2 point, Vector2 l1, Vector2 l2);
}

/**
 * @brief The Polygon class A class representing a polygon
 */
class Polygon
{
public:
    /**
     * @brief Polygon The polygon constructor. Takes in a vector of points representing the polygon, with an edge between the first and last point in the list
     * @param p
     */
    Polygon(std::vector<Vector2 *> p) : points(p){}

    /**
     * @brief points A vector of Vector2 pointers representing the polygon. The first point is connected to the last point, and all points are connected to point + 1
     */
    std::vector<Vector2 *> points;
};

/**
 * @brief The Vector2 class: A simple 2D vector
 */
class Vector2
{
public:
    /**
     * @brief Vector2 The constructor. Takes in an x and y value, and defaults to 0.
     * @param _x The x value of the vector
     * @param _y The y value of the vector
     */
    Vector2(double _x = 0, double _y = 0): x(_x), y(_y) {}

    /**
     * @brief operator [] Overloading the square bracket operator to allow you to access the x and y value using 0 for x, and 1 for y.
     *      Defaults to x on other integers
     * @param i
     * @return A reference to either the x or y value of the vector
     */
    double& operator [](int i);

    /**
     * @brief x The x value of the vector
     */
    double x;

    /**
     * @brief y The y value of the vector
     */
    double y;
};

/**
 * @brief The Vector3 class A 3D vector
 */
class Vector3
{
public:
    /**
     * @brief Vector3 A constructor to set the x, y, z values of the vector. Defaults to 0.
     * @param _x
     * @param _y
     * @param _z
     */
    Vector3(double _x = 0, double _y = 0, double _z = 0): x(_x), y(_y), z(_z) {}

    /**
     * @brief operator [] Overloading the square brackets to access the x,y, and z values by integer.
     *      0 accesses x, 1 accesses y, and 2 accesses z. Every other value accesses x.
     * @param i
     * @return
     */
    double& operator [](int i);

    double x;
    double y;
    double z;
};

/**
 * @brief A 2x2 Matrix class
 */
class Matrix22
{
public:

    /**
     * @brief Matrix22 The constructor for Matrix22. Takes in two vectors, and places them as the rows
     *      of the 2x3 matrix
     * @param x
     * @param y
     */
    Matrix22(Vector2 x, Vector2 y);

    /**
     * @brief Matrix22 A constructor that takes in a 2x2 array, and creates the Matrix22 object.
     * @param m The 2x2 array representing the 2x2 matrix
     */
    Matrix22(double m[][2]);

    /**
     * @brief operator () Overloading the parenthese to access any element in the matrix by calling m(i,j)
     * @param i: The row of the matrix
     * @param j: The column of the matrix
     * @return A reference to the value at position i,j
     */
    double& operator ()(int i, int j) {return matrix[i][j];}

    /**
     * @brief determinant Finds the determinant of the 2x2 matrix
     * @return A double representing the 2x2 matrix
     */
    double determinant();

    /**
     * @brief printme DEBUG ONLY. Outputs the matrix contents to console
     */
    void printme();

private:
    /**
     * @brief matrix An array representing the inner structure of the 2x2 matrix
     */
    double matrix[2][2];
};

/**
 * @brief A 3x3 Matrix class
 */
class Matrix33
{
public:
    /**
     * @brief Matrix33 A constructor that zeroes all entries in the matrix
     */
    Matrix33();

    /**
     * @brief Matrix33 A constructor that takes in 3 Vector3 objects. Each vector is set as a row in the matrix.
     *      Vector x takes the top row, y the middle row, and z the bottom row.
     * @param x
     * @param y
     * @param z
     */
    Matrix33(Vector3 x, Vector3 y, Vector3 z);

    /**
     * @brief Matrix33 A constructor that takes in a 3x3 array, and creates the Matrix33 object.
     * @param m The 3x3 array representing the matrix
     */
    Matrix33(double m[][3]);

    /**
     * @brief multiply Multplies the matrix by some other 3x3 Matrix m, and returns the product
     * @param m The matrix to multiply by
     * @return The product of multiplication of this * m
     */
    Matrix33 multiply(Matrix33 m);

    /**
     * @brief multiply Multiplies the matrix by some Vector3 object.
     * @param v The 3D vector to multiply by
     * @return The product of the multiplication of this * v
     */
    Vector3 multiply(Vector3 v);

    /**
     * @brief multiply Transforms the 2D vector into a 3D vector with a Z value of 1. Then, multiplies
     *      the matrix by this new 3D vector. It will then homogenize the resulting product which is a 3D vector
     *      into a 2D vector
     * @param v The 2D vector to multiply by
     * @return The homogenized product of this * [v.x, v.y, 1]
     */
    Vector2 multiply(Vector2 v);

    /**
     * @brief printme Outputs the contents of the 3x3 matrix to the console
     */
    void printme();

    /**
     * @brief inverse Computes the inverse of the of the matrix, and returns the 3x3 inverse
     * @return The 3x3 inverted matrix
     */
    Matrix33 inverse();

    /**
     * @brief cofactor Computes the cofactor of the matrix, and returns the 3x3 cofactor matrix
     * @return The 3x3 cofactor matrix
     */
    Matrix33 cofactor();

    /**
     * @brief adjoint Computes the adjoint of the matrix
     * @return The 3x3 adjointed matrix
     */
    Matrix33 adjoint();

    /**
     * @brief determinant Computes the determinant of the 3x3 matrix
     * @return A double representing the determinant of the matrix
     */
    double determinant();

    /**
     * @brief operator () Overloading the parenthesese to access any element at i,j in
     *      the matrix, where i is the row, and j is the column
     * @param i
     * @param j
     * @return A reference to the value at position i,j
     */
    double& operator ()(int i, int j) {return matrix[i][j];}

    /**
     * @brief operator * Overloads the operator to perform the multiplication of two matrices
     * @param m
     * @return The product of this * m
     */
    Matrix33 operator *(Matrix33 m) {return multiply(m);}

    /**
     * @brief operator * Overloads the operator to perform the multiplication of the matrix by a 3D vector
     * @param v
     * @return The product of this * v
     */
    Vector3 operator *(Vector3 v) {return multiply(v);}

    /**
     * @brief operator * Overloads the operator to perform the multiplication of the matrix by a 2D vector
     * @param v
     * @return The homogenized product of this * [v.x, v.y, 1]
     */
    Vector2 operator *(Vector2 v) {return multiply(v);}

    /**
     * @brief toString Returns a string representing the contents of the matrix
     * @return A QString representing the contents of the matrix
     */
    QString toString();

private:
    double matrix[3][3];
};

/**
 * @brief The MatrixStack class. It represents a stack of transformation matrices being pushed, and
 *      has a reference to a running product of the stack
 */
class MatrixStack
{
public:
    /**
     * @brief MatrixStack Constructor for the stack. Clears the stack, and assigns the product to a 3x3 identity matrix
     */
    MatrixStack();

    /**
     * @brief pop Pops the last matrix added from the top of the stack, and returns a pointer to it. Will also
     *      multiply the product by the inverse of the popped matrix
     * @return The popped matrix
     */
    Matrix33 * pop();

    /**
     * @brief push Pushes a 3x3 matrix to the stack, and multiplies the matrix by the current stack product
     * @param m
     */
    void push(Matrix33 * m);

    /**
     * @brief get_product The value of the product
     * @return The value of the product
     */
    Matrix33 get_product();

    /**
     * @brief size The current size of the stack
     * @return The size of the stack
     */
    int size();

    /**
     * @brief peek Peeks at the value on the top of the stack.
     * @return The value at the top of the stack
     */
    Matrix33 peek();

    /**
     * @brief toString Returns a string of all the contents of the matrices in the stack.
     * @return A string of all the matrices in the stack
     */
    QString toString();
private:
    /**
     * @brief stack A stack of pointers to 3D matrices.
     */
    QStack<Matrix33 *> stack;

    /**
     * @brief product The stack's current product
     */
    Matrix33 * product;
};

#endif // LINEARALG_H
