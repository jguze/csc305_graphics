#include "linearalg.h"



/******* Vector2 ******/

double& Vector2::operator [](int i)
{
    switch(i)
    {
        case 0:
            return x;
        case 1:
            return y;
        default:
            return x;
    }
}

/******* Vector3 ******/

double& Vector3::operator [](int i)
{
    switch(i)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return x;
    }
}

/******* Matrix22 ******/

Matrix22::Matrix22(Vector2 x, Vector2 y)
{
    for (int i = 0; i < 2; i++)
    {
        matrix[0][i] = x[i];
        matrix[1][i] = y[i];
    }
}

Matrix22::Matrix22(double m[][2])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matrix[i][j] = m[i][j];
        }
    }
}

double Matrix22::determinant()
{
    return linalg::determinant22(*this);
}

void Matrix22::printme()
{
    QDebug dbg(QtDebugMsg);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            dbg << (*this)(i,j);
        }
        dbg << "\n";
    }
}

/******* Matrix33 ******/

Matrix33::Matrix33()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

Matrix33::Matrix33(Vector3 x, Vector3 y, Vector3 z)
{
    for (int i = 0; i < 3; i++)
    {
        matrix[0][i] = x[i];
        matrix[1][i] = y[i];
        matrix[2][i] = z[i];
    }
}

Matrix33::Matrix33(double m[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = m[i][j];
        }
    }
}

Matrix33 Matrix33::inverse()
{
    return linalg::inverse33(*this);
}

double Matrix33::determinant()
{
    return linalg::determinant33(*this);
}

Matrix33 Matrix33::cofactor()
{
    return linalg::cofactor33(*this);
}

Matrix33 Matrix33::adjoint()
{
    return linalg::adjoint33(*this);
}

Matrix33 Matrix33::multiply(Matrix33 m)
{
    Matrix33 t;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
           t(i,j) = (*this)(i,0) * m(0, j) + (*this)(i, 1) * m(1, j) + (*this)(i, 2) * m(2,j);
        }
    }
    return t;
}

Vector3 Matrix33::multiply(Vector3 v)
{
    Vector3 t;
    for (int i = 0; i < 3; i++)
    {
        t[i] = ((*this)(i,0)) * (v[0]) + ((*this)(i, 1)) * v[1] + ((*this)(i, 2)) * (v[2]);
    }
    return t;
}

Vector2 Matrix33::multiply(Vector2 v)
{
    Vector3 u = multiply(Vector3(v.x, v.y, 1));
    u.x /= u.z;
    u.y /= u.z;
    return Vector2(u.x, u.y);
}

void Matrix33::printme()
{
    QDebug dbg(QtDebugMsg);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            dbg << (*this)(i,j);
        }
        dbg << "\n";
    }
}

QString Matrix33::toString()
{
    QString q = "";
    std::ostringstream strs;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            strs << (*this)(i,j) << " ";
        }
        strs << "\n";
    }
    strs << "\n";
    return QString(strs.str().c_str());
}

/******* MatrixStack ******/

MatrixStack::MatrixStack()
{
    // Reserve at least 10 places on the stack
    stack.reserve(10);
    //Initialize the product to a 3x3 identity matrix
    product = new Matrix33(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));
}

// If the stack is empty, return NULL
Matrix33 * MatrixStack::pop()
{
    if (stack.size() < 1)
        return NULL;
    Matrix33 * popped = stack.pop();
    *product = *product * (popped->inverse());
    return popped;
}

void MatrixStack::push(Matrix33 *m)
{
    stack.push(m);
    *product = *product * (*m);
}

Matrix33 MatrixStack::get_product()
{
    return *product;
}

Matrix33 MatrixStack::peek()
{
    if (!stack.isEmpty())
        return *stack.top();
    else
        return NULL;
}

QString MatrixStack::toString()
{
    QString s = "";
    if (stack.size() < 1)
    {
        return s + "EMPTY";
    }
    for (int i = stack.size() - 1; i >= 0; i--)
    {
        s += (stack[i])->toString();
    }
    return s;
}

int MatrixStack::size()
{
    return stack.size();
}


/**********************/

double linalg::determinant22(Matrix22 m)
{
    return m(0,0) * m(1,1) - m(0,1) * m(1,0);
}

// The determinant of a 3x3 us the actually the determinant of various smaller 2x2 matrices within the 3x3
double linalg::determinant33(Matrix33 m)
{
    double a[][2] = { {m(1,1), m(1,2)}, {m(2,1), m(2,2)} };
    double b[][2] = { {m(1,0), m(1,2)}, {m(2,0), m(2,2)} };
    double c[][2] = { {m(1,0), m(1,1)}, {m(2,0), m(2,1)} };
    return m(0,0) * determinant22(Matrix22(a)) - m(0,1) * determinant22(Matrix22(b)) + m(0,2) * determinant22(Matrix22(c));
}

// Returns the cofactor matrix of a 3x3 matrix
Matrix33 linalg::cofactor33(Matrix33 m)
{
    double a[][3] = { {1, -1, 1}, {-1, 1, -1}, {1, -1, 1} };
    Matrix33 cofactor(a);
    double temp_m[2][2];
    int r = 0;
    int s = 0;
    for (int i = 0; i < 3; i++, r = 0)
    {
        if (i == 1)
            r = 1;
        for (int j = 0; j < 3; j++, s = 0)
        {
            if (j == 1)
                s = 1;

            temp_m[0][0] = m( (i + 1 + r) % 3, (j + 1 + s) % 3);
            temp_m[0][1] = m( (i + 1 + r) % 3, (j + 2 - s) % 3);
            temp_m[1][0] = m( (i + 2 - r) % 3, (j + 1 + s) % 3);
            temp_m[1][1] = m( (i + 2 - r) % 3, (j + 2 - s) % 3);
            cofactor(i, j) *= determinant22(Matrix22(temp_m));
        }
    }
    return cofactor;
}

// Basic swap on a matrix
Matrix33 linalg::transpose33(Matrix33 m)
{
    double temp;
    temp = m(0,1);
    m(0,1) = m(1,0);
    m(1,0) = temp;

    temp = m(0,2);
    m(0,2) = m(2,0);
    m(2,0) = temp;

    temp = m(1,2);
    m(1,2) = m(2,1);
    m(2,1) = temp;
    return m;
}

// The adjoint is the transpose of the cofactor matrix
Matrix33 linalg::adjoint33(Matrix33 m)
{
    return transpose33(cofactor33(m));
}

Matrix33 linalg::inverse33(Matrix33 m)
{
    double determinant = determinant33(m);
    Matrix33 new_m = adjoint33(m);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            new_m(i, j) /= determinant;
        }
    }
    return new_m;
}

// Creates a 3x3 matrix that can be used to translate a 2d vector by the amount in Vector2 v;
Matrix33 * linalg::translate2(Vector2 v)
{
    double a[][3] = {{1,0,v.x}, {0,1,v.y}, {0,0,1}};
    return new Matrix33(a);
}

Matrix33 * linalg::translate2(double x, double y)
{
    return translate2(Vector2(x,y));
}

//Creates a 3x3 matrix that can be used to rotate a 2d vector by angle
Matrix33 * linalg::rotate2(double angle)
{
    angle = angle * PI / 180.0;
    double a[][3] = { {cos(angle), -1 * sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1} };
    return new Matrix33(a);
}

Matrix33 * linalg::scale2(Vector2 v)
{
    double a[][3] = {{v.x, 0, 0}, {0, v.y, 0}, {0, 0, 1}};
    return new Matrix33(a);
}

Matrix33 * linalg::scale2(double x, double y)
{
    return scale2(Vector2(x,y));
}

bool linalg::raycastAlgorithm(Vector2 v, Polygon p)
{
    int intersects = 0;
    bool isFirst = true;
    Vector2 prevPoint;
    Vector2 origin(0, v.y);
    int i = 0;
    for (std::vector<Vector2 *>::iterator it = p.points.begin(); it != p.points.end(); it++)
    {
        if (!isFirst)
        {
            if (linesIntersect(origin, v, *(*it), prevPoint))
            {
                intersects += 1;
            }
        } else {
            isFirst = false;
        }
        prevPoint = *(*it);
        i++;
    }
    if (linesIntersect(origin, v, *p.points.front(), *p.points.back()))
    {
        intersects += 1;
        qDebug() << i;
    }

    qDebug() << intersects;
    return (intersects % 2) != 0;
}

// The cross product of two 2D vectors is essentially just the determinant of a 2x2 matrix with
// each vector as a row in the matrix
double linalg::crossProduct(Vector2 a, Vector2 b)
{
    return Matrix22(a,b).determinant();
}

bool linalg::pointOnLine(Vector2 point, Vector2 l1, Vector2 l2)
{
    // As floating point is not perfect, we take the absolute value, and ensure it is less than some epsilon
    return fabs(distance(point, l1) + distance(point, l2) - distance(l1, l2)) <= EPSILON;
}

double linalg::distance(Vector2 a, Vector2 b)
{
    return sqrt( pow(a.y - b.y, 2) + pow(a.x -b.x, 2));
}

bool linalg::linesIntersect(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2)
{
    Vector2 p;
    double denom = (a1.x - a2.x) * (b1.y - b2.y) - (a1.y - a2.y) * (b1.x - b2.x);
    qDebug() << denom;
    if (fabs(denom) <= EPSILON)
        return false;

    double aCross = linalg::crossProduct(a1, a2);
    double bCross = linalg::crossProduct(b1, b2);
    p.x = ( aCross * (b1.x - b2.x) - (a1.x - a2.x) * bCross ) / denom;
    p.y = ( aCross * (b1.y - b2.y) - (a1.y - a2.y) * bCross ) / denom;
    return pointOnLine(p, a1, a2) && pointOnLine(p, b1, b2);
}
