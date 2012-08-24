/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_OBJECT_H_
#define _FLX_OBJECT_H_

#include "backend/cpp.h"
#include "FlxBasic.h"
#include "FlxVector.h"
#include "FlxRect.h"

/*
*  Base for all drawable entities
*/
class FlxObject : public FlxBasic {

public:

    // X position on screen
    float x;

    // Y position on screen
    float y;

    // width of the entity
    int width;

    // height of the entity
    int height;

    // linear velocity of object
    FlxVector velocity;

    // acceleration of the entity
    FlxVector acceleration;

    // maximum velocity of object
    FlxVector maxVelocity;

    // rotation speed
    float angularVelocity;

    // rotation of entity
    float angle;

    // scale
    FlxVector scale;

    // color
    int color;

    // is entity visible or not?
    bool visible;

    // entity's hitbox
    FlxRect hitbox;

    // hitbox move vector
    FlxVector hitboxMove;

    // is entity collidable?
    bool collidate;


    // get entity's center point
    FlxVector getCenter();

    // entity overlap override
    virtual FlxBasic* overlaps(FlxBasic *object);

    // check overlap and make some phycics work
    virtual FlxBasic* collide(FlxBasic *object);

    // default contructor
    FlxObject();

    // base update function (to override)
    virtual void update();

    // base rendering function (to override)
    virtual void draw();
};

#endif

