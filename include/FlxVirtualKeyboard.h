/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_VIRT_KEYBOARD_H_
#define _FLX_VIRT_KEYBOARD_H_

#include "FlxSprite.h"
#include "FlxButton.h"
#include "FlxGroup.h"

/**
*  On-screen virtual keyboard
*  Useful widget for mobile platforms with touch-screens
*/
class FlxVirtualKeyboard : public FlxGroup {

private:
    void pressedCallback(FlxButton*);
    void releasedCallback(FlxButton*);
public:

    /**
	*  Is virtual caps lock turned on?
	*/
    bool capsLock;

	
	/**
	*  Default constructor
	*  @param x Postion in X-axis
	*  @param y Postion in Y-axis
	*  @param backgroundImg Path to keyboard background image
	*  @param buttonImg Single button background
	*  @param buttonW Single button width
	*  @param buttonH Single button height
	*  @param buttonFont Path to font
	*  @param buttonFontSize Size of text
	*  @param buttonFontColor Color of text
	*  @param spacingX Spacing of single key in X-axis
	*  @param spacingY Spacing of single key in Y-axis
	*/
    FlxVirtualKeyboard(float x, float y, const char *backgroundImg, const char *buttonImg, int buttonW, int buttonH,
                       const char *buttonFont, int buttonFontSize, int buttonFontColor,
                       float spacingX = 20.f, float spacingY = 20.f);

	/**
	*  Default destructor
	*/
    virtual ~FlxVirtualKeyboard();
};

#endif

