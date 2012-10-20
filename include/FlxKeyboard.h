/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_KEYBOARD_H_
#define _FLX_KEYBOARD_H_

#include "FlxKey.h"
#include "backend/cpp.h"

/**
*  Keyboard handler
*/
class FlxKeyboard {

private:
    bool lastState[1024];
    bool simulate[1024];
public:

	/**
	*  Default constructor
	*/
    FlxKeyboard();
	
	/**
	*  Is specified key down?
	*  @param code Key code
	*  @return <code>true</code> if key is down, <code>false</code> is key is up
	*/
    bool down(FlxKey::KeyCode code);
	
	/**
	*  Is specified key just pressed?
	*  @param code Key code
	*  @return <code>true</code> if key is pressed, <code>false</code> is key is not pressed
	*/
    bool pressed(FlxKey::KeyCode code);
	
	/**
	*  Is specified key just released?
	*  @param code Key code
	*  @return <code>true</code> if key is pressed, <code>false</code> is key is not released
	*/
    bool released(FlxKey::KeyCode code);

	/**
	*  Simulate that specified key is down
	*  @param code Key to simulate
	*/
    void simulateKeyDown(FlxKey::KeyCode code);
	
	/**
	*  Stop simulating specified key
	*  @param code Key to stop simulating
	*/
    void simulateKeyUp(FlxKey::KeyCode code);

	/**
	*  Update keyboard state (Internal! Do not touch!)
	*/
    void updateState();
};

#endif

