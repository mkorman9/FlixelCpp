/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_U_H_
#define _FLX_U_H_

#include "backend/cpp.h"

/**
*  Support utility class
*/
class FlxU {

public:

	/**
	*  PI constant
	*/
    static const float PI;

	/**
	*  Create a ranom floating point number from range 0 - 1
	*  @return Random number
	*/
    static float random() {
        return random(0.0f, 1.0f);
    }
	
	/**
	*  Create a ranom floating point number from range min - max
	*  @param min Lower bound
	*  @param max Upper bound
	*  @return Random number
	*/
    static float random(float min, float max) {
        return (float)rand() / RAND_MAX * (max - min) + min;
    }

	/**
	*  Create a ranom floating integer number from range min - max
	*  @param min Lower bound
	*  @param max Upper bound
	*  @return Random number
	*/
    static int random(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

	/**
	*  Convert angle from degrees to radians 
	*  @param degrees Angle in degrees
	*  @return Converted angle
	*/
    static float degreesToRad(float degrees) {
        return degrees * (PI / 180.f);
    }

	/**
	*  Convert angle from radians to degrees 
	*  @param radians Angle in radians
	*  @return Converted angle
	*/
    static float radToDegrees(float rad) {
        return rad * (180.f / PI);
    }

	/**
	*  Convert integer value to ASCII string
	*  @param value Integer value to convert
	*  @return ASCII string
	*/
    static std::string toString(int value) {
        std::stringstream ss;
        ss << value;

        return ss.str();
    }
	
	/**
	*  Convert floating point value to ASCII string
	*  @param value Floating point value to convert
	*  @return ASCII string
	*/
    static std::string toString(float value) {
        std::stringstream ss;
        ss << value;

        return ss.str();
    }

	/**
	*  Convert integer value to Unicode string
	*  @param value Integer value to convert
	*  @return Unicode string
	*/
    static std::wstring toStringUnicode(int value) {
        std::wstringstream ss;
        ss << value;

        return ss.str();
    }

	/**
	*  Convert floating point value to Unicode string
	*  @param value Floating point value to convert
	*  @return Unicode string
	*/
    static std::wstring toStringUnicode(float value) {
        std::wstringstream ss;
        ss << value;

        return ss.str();
    }
	
	/**
	*  Convert ASCII string to integer value
	*  @param str String to convert
	*  @return Integer value
	*/
    static int toNumber(const std::string& str) {
        std::stringstream ss(str);
        int value;

        ss >> value;
        return value;
    }

	/**
	*  Convert ASCII string to floating point value
	*  @param str String to convert
	*  @return Floating point value
	*/
    static float toFloatNumber(const std::string& str) {
        std::stringstream ss(str);
        float value;

        ss >> value;
        return value;
    }
	
	/**
	*  Convert Unicode string to integer value
	*  @param str String to convert
	*  @return Integer value
	*/
    static int toNumberUnicode(const std::wstring& str) {
        std::wstringstream ss(str);
        int value;

        ss >> value;
        return value;
    }
	
	/**
	*  Convert Unicode string to floating point value
	*  @param str String to convert
	*  @return Floating point value
	*/
    static float toFloatNumberUnicode(const std::wstring& str) {
        std::wstringstream ss(str);
        float value;

        ss >> value;
        return value;
    }
};

#endif

