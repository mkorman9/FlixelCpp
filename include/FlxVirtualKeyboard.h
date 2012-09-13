/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_VIRT_KEYBOARD_H_
#define _FLX_VIRT_KEYBOARD_H_

#include "FlxSprite.h"
#include "FlxButton.h"
#include "FlxGroup.h"

/*
*  On-screen virtual keyboard
*  Useful widget for mobile platforms
*/
class FlxVirtualKeyboard : public FlxGroup {

private:
    void pressedCallback(FlxButton*);
    void releasedCallback(FlxButton*);
public:

    // is virtual caps lock turned on?
    bool capsLock;


    FlxVirtualKeyboard(float x, float y, const char *backgroundImg, const char *buttonImg, int buttonW, int buttonH,
                       const char *buttonFont, int buttonFontSize, int buttonFontColor,
                       float spacingX = 20.f, float spacingY = 20.f);
};

#endif

