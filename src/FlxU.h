/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_U_H_
#define _FLX_U_H_

#include "backend/cpp.h"

/*
*  Support utility class
*/
class FlxU {

public:

    static float random() {
        return (float)rand() / (float)RAND_MAX;
    }

    static float random(float min, float max) {
        return (random() * (max - min)) + min;
    }

    static int random(int min, int max) {
        return floor(random() * (max - min + 1)) + min;
    }

    static float degreesToRad(float deegrees) {
        return deegrees / 57.2957795f;
    }

    static float radToDegrees(float rad) {
        return rad * 57.2957795f;
    }

    static std::string toString(int value) {
        std::stringstream ss;
        ss << value;

        return ss.str();
    }

    static std::string toString(float value) {
        std::stringstream ss;
        ss << value;

        return ss.str();
    }

    static float toNumber(const std::string& str) {
        std::stringstream ss(str);
        int value;

        ss >> value;
        return value;
    }
};

#endif

