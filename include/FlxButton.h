/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_BUTTON_H_
#define _FLX_BUTTON_H_

#include "FlxSprite.h"
#include "FlxText.h"
#include "FlxGroup.h"

/**
*  Interactive button class
*/
class FlxButton : public FlxGroup {

private:
    int buttonStates;
public:

    /**
	*  Sprite which represents button's background
	*/
    FlxSprite *sprite;

    /**
	*  Text which is visible when button is currently pressed
	*/
    FlxText *onText;

    /**
	*  Text which is visible when button is not currently pressed
	*/
    FlxText *offText;

    /**
	*  Should button support multitouch or just check first available mouse device.
	*/
    bool multitouch;

    /**
	*  Is button currently down?
	*/
    bool down;

    /**
	*  Just pressed?
	*/
    bool pressed;

    /**
	*  Just released?
	*/
    bool released;

    /**
	*  Is mouse over button.
	*  NOTE: PC platforms only
	*/
    bool mouseOver;

    /**
	*  Button position in screen space
	*/
    float x, y;

    /**
	*  Button size
	*/
    float width, height;

    /**
	*  Event called when button is down
	*/
    std::function<void(FlxButton*)> onDown;
	
	/**
	*  Event called when button is just pressed
	*/
    std::function<void(FlxButton*)> onPressed;
	
	/**
	*  Event called when button is just released?
	*/
    std::function<void(FlxButton*)> onReleased;

	/**
	*  Default constructor
	*  @param x X-position in screen space
	*  @param y Y-position in screen space
	*  @param buttonImage Path to button background image (must be in device's local storage)
	*  @param width Width of button
	*  @param height Height of button
	*  @param statesCount Number of states which present on button's image (1 - just one state, 2 - up-state and down-state,
			3 - up-state, down-state, and mouse-over state).
	*/
    FlxButton(float x, float y, const char *buttonImage, int width, int height, int statesCount = 2);

	/**
	*  Set button's text format.
	*  @param text Default button's text (in Unicode)
	*  @param font Path to font (must be in device's local storage)
	*  @param size Font's size
	*  @param color Text's color
	*/
    void setTextFormat(const wchar_t *text, const char *font, int size, int color);

	/**
	*  Overrided <code>update()</code> event
	*/
    virtual void update();
	
	/**
	*  Overrided <code>draw()</code> event
	*/
    virtual void draw();
};

#endif


