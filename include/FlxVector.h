/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_VECTOR_H_
#define _FLX_VECTOR_H_

#include "backend/cpp.h"

/**
*  Help vector class (in 2D space)
*/
class FlxVector {

public:

    /**
	*  Value of vector in X-axis
	*/
    float x;

    /**
	*  Value of vector in Y-axis
	*/
    float y;

    /**
	*  Reference counter. Used in script engine.
	*  (Internal! Do not touch!)
	*/
    int _refCount;

	
	/**
	*  Default constructor
	*/
    FlxVector() {
        x = y = 0.f;
        _refCount = 1;
    }

	/**
	*  Copying constructor
	*  @param other Vector to copy
	*/
    FlxVector(const FlxVector& other) {
        x = other.x;
        y = other.y;

        _refCount = 1;
    }
	
	/**
	*  Constructor with 2 parameters
	*  @param X Value of vector in X-axis
	*  @param Y Value of vector in Y-axis
	*/
    FlxVector(float X, float Y) {
        x = X;
        y = Y;

        _refCount = 1;
    }
	
	/**
	*  Constructor with 4 parameters
	*  @param X1 Start point of vector in X-axis
	*  @param Y1 Start point of vector in Y-axis
	*  @param X1 End point of vector in X-axis
	*  @param Y1 End point of vector in Y-axis
	*/
    FlxVector(float X1, float Y1, float X2, float Y2) {
        x = X2 - X1;
        y = Y2 - Y1;

        _refCount = 1;
    }
	
	/**
	*  Constructor with 2 other object references
	*  @param vec1 Start point of vector
	*  @param vec2 End point of vector
	*/
    FlxVector(const FlxVector &vec1, const FlxVector &vec2) {
        x = vec2.x - vec1.x;
        y = vec2.y - vec1.y;

        _refCount = 1;
    }
	
	/**
	*  Calculate length of vector
	*  @return Length of vector
	*/
    float length() const {
        return (float) std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }
	
	/**
	*  Normalize object to directional vector
	*  @return Reference to <code>this</code>
	*/
    FlxVector& normalize() {

        x = x / length();
        y = y / length();

        return *this;
    }
	
	/**
	*  Calculate angle between vector and X-axis
	*  @return Calculated angle
	*/
    float getAngle() const {
        return std::atan2(y, x);
    }
	
	/**
	*  Rotate vector around (0,0) point by specified angle
	*  @param angle Angle to rotate
	*  @return Reference to <code>this</code>
	*/
    FlxVector& rotate(float angle) {
        FlxVector other(*this);

        other.x = (x * std::cos(angle)) - (y * std::sin(angle));
        other.y = (x * std::sin(angle)) + (y * std::cos(angle));

        x = other.x;
        y = other.y;

        return *this;
    }
	
	/**
	*  Rotate vector around specified point by specified angle
	*  @param angle Angle to rotate
	*  @param point Point to rotate around
	*  @return Reference to <code>this</code>
	*/
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

	
    // all operators
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
