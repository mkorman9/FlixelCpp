/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_BASIC_H_
#define _FLX_BASIC_H_

#include "backend/cpp.h"
#include "FlxVector.h"

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

    // collision callback typew
    typedef std::function<void(FlxBasic*, FlxBasic*)> CollisionCallback;

    // entity type
    FlxEntityType entityType;

    // is entity active or not?
    bool active;

    // is object scrool-able
    bool scrool;

    // scrool modifier
    FlxVector scroolFactor;

    // special variables
    //std::map<std::string, std::string> vars;


    // default contructor
    FlxBasic() {
        active = true;
        scrool = true;
        scroolFactor.x = scroolFactor.y = 1.f;
    }

    // base update function (to override)
    virtual void update() {
    }

    // base rendering function (to override)
    virtual void draw() {
    }

    // kill entity
    virtual void kill() {
        active = false;
    }

    // entity collidates with something?
    virtual FlxBasic* overlaps(FlxBasic *object, const CollisionCallback& callback = nullptr) {
        return NULL;
    }

    // check overlap and make some phycics work
    virtual FlxBasic* collide(FlxBasic *object, const CollisionCallback& callback = nullptr) {
        return NULL;
    }
};

#endif


