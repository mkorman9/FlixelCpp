/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_KEYBOARD_H_
#define _FLX_KEYBOARD_H_

#include "FlxKey.h"
#include "backend/cpp.h"

/*
*  Keyboard handler
*/
class FlxKeyboard {

private:
    bool lastState[1024];
public:

    FlxKeyboard();
    bool down(FlxKey::KeyCode code);
    bool pressed(FlxKey::KeyCode code);
    bool released(FlxKey::KeyCode code);

    void updateState();
};

#endif

