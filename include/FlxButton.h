/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_BUTTON_H_
#define _FLX_BUTTON_H_

#include "FlxSprite.h"
#include "FlxText.h"
#include "FlxGroup.h"

/*
*  Interactive button
*/
class FlxButton : public FlxGroup {

private:
    int buttonStates;
public:

    // button sprite
    FlxSprite *sprite;

    // text visible when button is currently pressed
    FlxText *onText;

    // text visible when button is not currently pressed
    FlxText *offText;

    // is button may be pressed only by one touch or it supports multitouch
    bool multitouch;

    // is button currently down
    bool down;

    // is button currently pressed
    bool pressed;

    // is button currently released
    bool released;

    // is mouse over button? (only PC)
    bool mouseOver;

    // button position
    float x, y;

    // button size
    float width, height;

    // callbacks
    std::function<void()> onDown;
    std::function<void()> onPressed;
    std::function<void()> onReleased;

    FlxButton(float x, float y, const char *buttonImage, int width, int height, int statesCount = 2);

    // set default text format
    void setTextFormat(const char *text, const char *font, int size, int color);

    virtual void update();
    virtual void draw();
};

#endif


