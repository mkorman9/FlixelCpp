/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_BASIC_H_
#define _FLX_BASIC_H_

#include "backend/cpp.h"
#include "FlxVector.h"

/**
*  Represents type of entity (single object or group of objects)
*  Simple RTTI mechanism
*/
enum FlxEntityType {
    FLX_OBJECT,
    FLX_GROUP
};


/**
*  Base for all entities in game. Represents every object behavior
*/
class FlxBasic {

public:

    /**
    *  Collision callback type. Used in <code>overlaps()</code> and <code>collide()</code>
    */
    typedef std::function<void(FlxBasic*, FlxBasic*)> CollisionCallback;

    /**
    *  Type of entity (single object or group of objects)
    */
    FlxEntityType entityType;

    /**
    *  Should entity be updated every frame.
    *  NOTE: If it's false - update() function won't be called every frame, but draw() will be.
    */
    bool active;

    /**
    *  Should entity be moved by scroolVector
    */
    bool scrool;

    /**
    *  Scrool modifier. Helpful for parallax scrooling.
    */
    FlxVector scroolFactor;

    /**
    *  Some user data. Helpful in scripts.
    */
    int flags;


    /**
    *  Default constructor
    */
    FlxBasic() {
        active = true;
        scrool = true;
        scroolFactor.x = scroolFactor.y = 1.f;
        flags = 0;
    }

    /**
    *  Destructior's template
    */
    virtual ~FlxBasic() {
    }

    /**
    *  Update event. It will be called every frame.
    *  NOTE: Template. Should be overrided later.
    */
    virtual void update() {
    }

    /**
    *  Rendering event. It will be called every frame.
    *  NOTE: Template. Should be overrided later.
    */
    virtual void draw() {
    }

    /**
    *  Deactivate entity
    */
    virtual void kill() {
        active = false;
    }

    /**
    *  Base template for collisions checking functions.
    *  @param object Object to check
    *  @param callback Callback to call (NOTE: if you pass FlxGroup as object, callback will receive
                                         single single group's element which overlaps)
    *  @return Always <code>NULL</code> because it is a template
    */
    virtual FlxBasic* overlaps(FlxBasic *object, const CollisionCallback& callback = nullptr) {
        (void)object; (void)callback;
        return NULL;
    }

    /**
    *  Base template for collisions checking functions. The main difference between <code>overlaps()</code>
    *  and <code>collide()</code> is that <code>collide()</code> also makes some physics work.
    *  @param object Object to check
    *  @param callback Callback to call (NOTE: if you pass FlxGroup as object, callback will receive
                                         single single group's element which overlaps)
    *  @return Always <code>NULL</code> because it is a template
    */
    virtual FlxBasic* collide(FlxBasic *object, const CollisionCallback& callback = nullptr) {
        (void)object; (void)callback;
        return NULL;
    }
};

#endif


