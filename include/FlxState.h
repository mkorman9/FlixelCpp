/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_STATE_H_
#define _FLX_STATE_H_

#include "backend/cpp.h"
#include "FlxGroup.h"

/*
*  Basic scene managment class
*/
class FlxState : public FlxGroup {

public:

    // desturctor
    ~FlxState() {
        clear();
    }

    // on create event (to override)
    virtual void create() {
    }

    // update all scene elements (to override)
    virtual void update() {
        FlxGroup::update();
    }

    // draw all scene elements (to override)
    void draw() {
        FlxGroup::draw();
    }
};

#endif
