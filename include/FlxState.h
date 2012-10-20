/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_STATE_H_
#define _FLX_STATE_H_

#include "backend/cpp.h"
#include "FlxGroup.h"

/**
*  Basic scene managment class
*/
class FlxState : public FlxGroup {

public:

    /**
	*  Default destrurctor
	*/
    ~FlxState() {
        clear();
    }

    /**
	*  State creating event. It's called once when state is being set as default.
	*  To override.
	*/
    virtual void create() {
    }

    /**
	*  State leaving event. It's called once when state is being destroyed (but before destructor).
	*  To override.
	*/
    virtual void leave() {
    }

    /**
	*  Update state event.
	*  To override.
	*/
    virtual void update() {
        FlxGroup::update();
    }

    /**
	*  Draw event.
	*  To override.
	*/
    void draw() {
        FlxGroup::draw();
    }
};

#endif
