/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_OBJECT_H_
#define _FLX_OBJECT_H_

#include "backend/cpp.h"
#include "FlxBasic.h"
#include "FlxRect.h"
#include "FlxPath.h"

/*
*  Base for all drawable entities
*/
class FlxObject : public FlxBasic {

private:
    FlxPath::Node currentNode;
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

    // color (in 24-bits) NO ALPHA!!!!1111
    int color;

    // is entity visible or not?
    bool visible;

    // entity's hitbox
    FlxRect hitbox;

    // hitbox move vector
    FlxVector hitboxMove;

    // is entity collidable?
    bool collisions;

    // opacity (0 - 1)
    float alpha;

    // is this element of GUI? If true - don't apply post effects
    bool isGUI;

    // is object following some path?
    bool isFollowingPath;

    // following velocity
    float followingVelocity;

    // path to follow
    FlxPath *pathToFollow;


    // get entity's center point
    FlxVector getCenter();

    // is entity touching floor
    bool isTouchingFloor(FlxBasic *floor);

    // is entity touching ceiling
    bool isTouchingCeiling(FlxBasic *ceil);

    // entity overlap override
    virtual FlxBasic* overlaps(FlxBasic *object, const CollisionCallback& callback = nullptr);

    // check overlap and make some phycics work
    virtual FlxBasic* collide(FlxBasic *object, const CollisionCallback& callback = nullptr);

    // follow some path
    void followPath(FlxPath *toFollow, float speed);

    // stop following path
    void stopFollowing();

    // kill entity
    virtual void kill();

    // default contructor
    FlxObject();

    // base update function (to override)
    virtual void update();

    // base rendering function (to override)
    virtual void draw();
};

#endif

