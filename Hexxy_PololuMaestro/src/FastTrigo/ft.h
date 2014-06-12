#ifndef FT_H
#define FT_H

#include <math.h>
#ifdef QT_GUI_LIB
#include <QtGui>
#endif
#include <intrin.h>
#include <xmmintrin.h>
#include <pmmintrin.h>

namespace FT
{
    float sqrt(float squared);
    float length(float x, float y);
    float length(float x, float y, float z);
    float atan2(float y, float x);
    float cos(float angle);
    float sin(float angle);
    void  sincos(float angle, float *sin, float *cos);
};

#endif