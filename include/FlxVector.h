/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_VECTOR_H_
#define _FLX_VECTOR_H_

#include "backend/cpp.h"

class FlxVector {

public:

    // x value of vector
    float x;

    // y value of vector
    float y;

    // default contructor
    FlxVector() {
        x = y = 0.f;
    }

    FlxVector(float X, float Y) {
        x = X;
        y = Y;
    }

    FlxVector(float X1, float Y1, float X2, float Y2) {
        x = X2 - X1;
        y = Y2 - Y1;
    }

    FlxVector(const FlxVector &vec1, const FlxVector &vec2) {
        x = vec2.x - vec1.x;
        y = vec2.y - vec1.y;
    }

    float length() {
        return (float) sqrt(pow(x, 2) + pow(y, 2));
    }

    FlxVector& normalize() {

        x = x / length();
        y = y / length();

        return *this;
    }

    float getAngle() {
        return atan2(y, x);
    }
};

#endif
