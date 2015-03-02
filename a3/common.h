#ifndef COMMON_H
#define COMMON_H
#include <QVector>
#include "linearalg.h"

enum Shape {CIRCLE, SQUARE, SPECIAL};
struct f_frame {
    QVector<FrenetCrossSection> crossSectionList;
    QVector<Triangle3> cylinderList;
    QVector<Triangle3> lids;
    bool noValue;
};

#endif // COMMON_H
