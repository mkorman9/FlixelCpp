/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_MOUSEHOLDER_H_
#define _FLX_MOUSEHOLDER_H_

#include "FlxMouse.h"
#include "FlxRect.h"

/**
*  Mouse abstraction layer
*/
class FlxMouseHolder {

public:

	/**
	*  Get total active mouse devices count
	*/
    int touchesCount();

    /**
	*  Get first available mouse device
	*  @return Pointer to first available device
	*/
    FlxMouse* first();

    /**
	*  Is left mouse button/touch (with specified ID) down? 
	*  @param index Device ID or <code>-1</code> if you want to check all devices
	*  @return Pointer to first device with left button down or <code>NULL</code>
	*/
    FlxMouse* down(int index = -1);

	/**
	*  Is left mouse button/touch (with specified ID) just pressed? 
	*  @param index Device ID or <code>-1</code> if you want to check all devices
	*  @return Pointer to first device with left button pressed or <code>NULL</code>
	*/
    FlxMouse* pressed(int index = -1);
	
	/**
	*  Is left mouse button/touch (with specified ID) just released? 
	*  @param index Device ID or <code>-1</code> if you want to check all devices
	*  @return Pointer to first device with left button released or <code>NULL</code>
	*/
    FlxMouse* released(int index = -1);
	
	/**
	*  Is left mouse button/touch (with specified ID) down and overlaps specified area? 
	*  @param area Area to check
	*  @param index Device ID or <code>-1</code> if you want to check all devices
	*  @return Pointer to first device with left button down or <code>NULL</code>
	*/
    FlxMouse* downOnArea(const FlxRect& area, int index = -1);

	/**
	*  Is left mouse button/touch (with specified ID) just pressed and overlaps specified area? 
	*  @param area Area to check
	*  @param index Device ID or <code>-1</code> if you want to check all devices
	*  @return Pointer to first device with left button pressed or <code>NULL</code>
	*/
    FlxMouse* pressedOnArea(const FlxRect& area, int index = -1);

	/**
	*  Is left mouse button/touch (with specified ID) just released and overlaps specified area? 
	*  @param area Area to check
	*  @param index Device ID or <code>-1</code> if you want to check all devices
	*  @return Pointer to first device with left button released or <code>NULL</code>
	*/
    FlxMouse* releasedOnArea(const FlxRect& area, int index = -1);

	/**
	*  Is middle mouse button down? (PC only)
	*  @return <code>true</code> if button is down, <code>false</code> if it's up
	*/
    bool middleDown();
	
	/**
	*  Is middle mouse button just pressed? (PC only)
	*  @return <code>true</code> if button is pressed, <code>false</code> if it's not
	*/
    bool middlePressed();
	
	/**
	*  Is middle mouse button just released? (PC only)
	*  @return <code>true</code> if button is released, <code>false</code> if it's not
	*/
    bool middleReleased();

	/**
	*  Is right mouse button down? (PC only)
	*  @return <code>true</code> if button is down, <code>false</code> if it's up
	*/
    bool rightDown();
	
	/**
	*  Is right mouse button just pressed? (PC only)
	*  @return <code>true</code> if button is pressed, <code>false</code> if it's not
	*/
    bool rightPressed();
	
	/**
	*  Is right mouse button just released? (PC only)
	*  @return <code>true</code> if button is released, <code>false</code> if it's not
	*/
    bool rightReleased();
};

#endif

