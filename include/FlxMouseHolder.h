/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_MOUSEHOLDER_H_
#define _FLX_MOUSEHOLDER_H_

#include "FlxMouse.h"
#include "FlxRect.h"

/*
*  Mouse abstraction layer
*/
class FlxMouseHolder {

public:
    int touchesCount();

    // left mouse button or touch
    FlxMouse* first();

    FlxMouse* down(int index = -1);

    FlxMouse* pressed(int index = -1);

    FlxMouse* released(int index = -1);

    FlxMouse* downOnArea(const FlxRect& area, int index = -1);

    FlxMouse* pressedOnArea(const FlxRect& area, int index = -1);

    FlxMouse* releasedOnArea(const FlxRect& area, int index = -1);

    // PC specific
    bool middleDown();

    bool middlePressed();

    bool middleReleased();

    bool rightDown();

    bool rightPressed();

    bool rightReleased();
};

#endif

