/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_RECT_H_
#define _FLX_RECT_H_

/**
*  Rectangle class
*/
class FlxRect {

public:

	/**
	*  Position of top-left corner in X-axis
	*/
    float x;
	
	/**
	*  Position of top-left corner in Y-axis
	*/
    float y;
	
	/**
	*  Width of rectangle
	*/
    int width;
	
	/**
	*  Height of the rectangle
	*/
    int height;
	
	/**
	*  Reference counter (used in script engine). It's internal anyway.
	*/
    int _refCount;
	
	
	/**
	*  Default constructor
	*  @param X Position of top-left corner in X-axis
	*  @param Y Position of top-left corner in Y-axis
	*  @param Width Width of rectangle
	*  @param Height Height of the rectangle
	*/
    FlxRect(float X = 0, float Y = 0, int Width = 0, int Height = 0) {
        x = X;
        y = Y;
        width = Width;
        height = Height;

        _refCount = 1;
    }
	
	/**
	*  Check collision of two rectangles
	*  @param second Retangle to check
	*  @return Calculations result
	*/
    bool overlaps(const FlxRect& second) const {
        return !((x >= (second.x + second.width)) || (second.x >= (x + width)) || (y >= (second.y + second.height))
            || (second.y >= (y + height)));
    }
};

#endif



