/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_BASIC_H_
#define _FLX_BASIC_H_

#include "backend/cpp.h"

enum FlxEntityType {
    FLX_OBJECT,
    FLX_GROUP
};

/*
*  Base for all entities.
*  Represents all objects in game
*/
class FlxBasic {

public:

    // entity type
    FlxEntityType entityType;

    // is entity active or not?
    bool active;

    // special variables
    std::map<std::string, std::string> vars;

    // default contructor
    FlxBasic() {
        active = true;
    }

    // base update function (to override)
    virtual void update() {
    }

    // base rendering function (to override)
    virtual void draw() {
    }

    // entity collidates with something?
    virtual FlxBasic* overlaps(FlxBasic *object) {
        return NULL;
    }

    // check overlap and make some phycics work
    virtual FlxBasic* collide(FlxBasic *object) {
        return NULL;
    }
};

#endif


