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

    static const float PI;

    static float random() {
        return random(0.0f, 1.0f);
    }

    static float random(float min, float max) {
        return (float)rand() / RAND_MAX * (max - min) + min;
    }

    static int random(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    static float degreesToRad(float deegrees) {
        return deegrees * (PI / 180.f);
    }

    static float radToDegrees(float rad) {
        return rad * (180.f / PI);
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

    static std::wstring toStringUTF8(int value) {
        std::wstringstream ss;
        ss << value;

        return ss.str();
    }

    static std::wstring toStringUTF8(float value) {
        std::wstringstream ss;
        ss << value;

        return ss.str();
    }

    static int toNumber(const std::string& str) {
        std::stringstream ss(str);
        int value;

        ss >> value;
        return value;
    }

    static float toFloatNumber(const std::string& str) {
        std::stringstream ss(str);
        float value;

        ss >> value;
        return value;
    }

    static int toNumberUTF8(const std::wstring& str) {
        std::wstringstream ss(str);
        int value;

        ss >> value;
        return value;
    }

    static float toFloatNumberUTF8(const std::wstring& str) {
        std::wstringstream ss(str);
        float value;

        ss >> value;
        return value;
    }
};

#endif

