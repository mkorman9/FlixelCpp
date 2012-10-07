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

    int _refCount;

    FlxVector() {
        x = y = 0.f;
        _refCount = 1;
    }

    FlxVector(const FlxVector& other) {
        x = other.x;
        y = other.y;

        _refCount = 1;
    }

    FlxVector(float X, float Y) {
        x = X;
        y = Y;

        _refCount = 1;
    }

    FlxVector(float X1, float Y1, float X2, float Y2) {
        x = X2 - X1;
        y = Y2 - Y1;

        _refCount = 1;
    }

    FlxVector(const FlxVector &vec1, const FlxVector &vec2) {
        x = vec2.x - vec1.x;
        y = vec2.y - vec1.y;

        _refCount = 1;
    }

    float length() const {
        return (float) std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    FlxVector& normalize() {

        x = x / length();
        y = y / length();

        return *this;
    }

    float getAngle() const {
        return std::atan2(y, x);
    }

    FlxVector& rotate(float angle) {
        FlxVector other(*this);

        other.x = (x * std::cos(angle)) - (y * std::sin(angle));
        other.y = (x * std::sin(angle)) + (y * std::cos(angle));

        x = other.x;
        y = other.y;

        return *this;
    }

    FlxVector& rotateAroundPoint(float angle, const FlxVector& point) {
        FlxVector other(*this);

        other.x = (((x - point.x) * std::cos(angle)) -
                   ((y - point.y) * std::sin(angle))) + point.x;
        other.y = (((x - point.x) * std::sin(angle)) +
                   ((y - point.y) * std::cos(angle))) + point.y;

        x = other.x;
        y = other.y;

        return *this;
    }

    // operators
    FlxVector operator+ (const FlxVector& other) {
        FlxVector product(*this);

        product.x += other.x;
        product.y += other.y;
        return product;
    }

    FlxVector operator- (const FlxVector& other) {
        FlxVector product(*this);

        product.x -= other.x;
        product.y -= other.y;
        return product;
    }

    FlxVector operator* (const FlxVector& other) {
        FlxVector product(*this);

        product.x *= other.x;
        product.y *= other.y;
        return product;
    }

    FlxVector operator/ (const FlxVector& other) {
        FlxVector product(*this);

        product.x /= other.x;
        product.y /= other.y;
        return product;
    }

    FlxVector operator! () {
        FlxVector product(*this);

        product.x = -x;
        product.y = -y;
        return product;
    }

    FlxVector& operator+= (const FlxVector& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    FlxVector& operator-= (const FlxVector& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    FlxVector& operator*= (const FlxVector& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    FlxVector& operator/= (const FlxVector& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    FlxVector operator+ (float scalar) {
        FlxVector product(*this);

        product.x += scalar;
        product.y += scalar;
        return product;
    }

    FlxVector operator- (float scalar) {
        FlxVector product(*this);

        product.x -= scalar;
        product.y -= scalar;
        return product;
    }

    FlxVector operator* (float scalar) {
        FlxVector product(*this);

        product.x *= scalar;
        product.y *= scalar;
        return product;
    }

    FlxVector operator/ (float scalar) {
        FlxVector product(*this);

        product.x /= scalar;
        product.y /= scalar;
        return product;
    }

    FlxVector& operator+= (float scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }

    FlxVector& operator-= (float scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    FlxVector& operator*= (float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    FlxVector& operator/= (float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};

#endif
