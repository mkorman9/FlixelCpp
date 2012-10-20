/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_MOUSE_H_
#define _FLX_MOUSE_H_

#include "backend/cpp.h"

/**
*  Structure representing single mouse device or touch
*/
struct FlxMouse {

private:
    bool lastLeftDown, lastRightDown, lastMiddleDown;
public:

	/**
	*  Is left mouse button down?
	*/
    bool leftDown;
	
	/**
	*  Is middle mouse button down?
	*/
	bool middleDown;

	/**
	*  Is right mouse button down?
	*/
	bool rightDown;
	
	/**
	*  Is left mouse button just pressed?
	*/
    bool leftPressed;
	
	/**
	*  Is middle mouse button just pressed?
	*/
	bool middlePressed;

	/**
	*  Is right mouse button just pressed?
	*/
	bool rightPressed;

	/**
	*  Is left mouse button just released?
	*/
    bool leftReleased;
	
	/**
	*  Is middle mouse button just released?
	*/
	bool middleReleased;

	/**
	*  Is right mouse button just released?
	*/
	bool rightReleased;
	
	/**
	*  Actual mouse position in X-axis
	*/
    float x;
	
	/**
	*  Position in X-axis where click was released (only in touch devices)
	*/
	float endX;
	
	/**
	*  Actual mouse position in Y-axis
	*/
    float y;
	
	/**
	*  Position in Y-axis where click was released (only in touch devices)
	*/
	float endY;

	/**
	*  Touch index
	*/
    int index;

	
	/**
	*  Default constructor
	*  @param id Touch device index
	*/
    FlxMouse(int id);
	
	/**
	*  Show hardware mouse cursor (only PC)
	*/
    void show();
	
	/**
	*  Hide hardware mouse cursor (only PC)
	*/
    void hide();

	/**
	*  Update mouse state (Internal! Do not touch!)
	*/
    void updateState();

    // static internal events
    static void onTouchBegin(int pointer, float, float);
    static void onTouchEnd(int pointer, float, float);
};

#endif

