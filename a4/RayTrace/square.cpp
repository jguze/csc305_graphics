#include "square.h"

Square::Square()
{
    vertices.push_back(-10);
    vertices.push_back(0);
    vertices.push_back(-10);

    vertices.push_back(10);
    vertices.push_back(0);
    vertices.push_back(-10);

    vertices.push_back(-10);
    vertices.push_back(0);
    vertices.push_back(10);

    vertices.push_back(10);
    vertices.push_back(0);
    vertices.push_back(10);


    vertices.push_back(-10);
    vertices.push_back(-2);
    vertices.push_back(-10);

    vertices.push_back(10);
    vertices.push_back(-2);
    vertices.push_back(-10);

    vertices.push_back(-10);
    vertices.push_back(-2);
    vertices.push_back(10);

    vertices.push_back(10);
    vertices.push_back(-2);
    vertices.push_back(10);


    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(0);

    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(1);


    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);

    indices.push_back(5);
    indices.push_back(7);
    indices.push_back(6);


    indices.push_back(4);
    indices.push_back(0);
    indices.push_back(5);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(5);


    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(7);

    indices.push_back(5);
    indices.push_back(1);
    indices.push_back(7);


    indices.push_back(7);
    indices.push_back(3);
    indices.push_back(2);

    indices.push_back(7);
    indices.push_back(2);
    indices.push_back(6);


    indices.push_back(6);
    indices.push_back(2);
    indices.push_back(0);

    indices.push_back(6);
    indices.push_back(0);
    indices.push_back(4);
}
