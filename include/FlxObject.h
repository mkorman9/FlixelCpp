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

// Special collision flags
#define FLX_NO_COLLISIONS_UP 0x00000001
#define FLX_NO_COLLISIONS_DOWN 0x00000010
#define FLX_NO_COLLISIONS_RIGHT 0x00000020
#define FLX_NO_COLLISIONS_LEFT 0x00000100


/**
*  Base for all drawable entities
*/
class FlxObject : public FlxBasic {

private:
    FlxPath::Node currentNode;
public:

    /**
	* X position on screen
	*/
    float x;

	/**
	* Y position on screen
	*/
    float y;

	/**
	* Width of the entity
	*/
    int width;

	/**
	* Height of the entity
	*/
    int height;

	/**
	* Linear velocity of object
	*/
    FlxVector velocity;

	/**
	* Acceleration of the entity
	*/
    FlxVector acceleration;

	/**
	* Maximum velocity of object
	*/
    FlxVector maxVelocity;

	/**
	* Rotation speed
	*/
    float angularVelocity;

	/**
	* Rotation of entity
	*/
    float angle;

	/**
	* Scale factor
	*/
    FlxVector scale;

	/**
	* Color mask, <b>24-bits without alpha</b>
	*/
    int color;

	/**
	* Is entity visible or not?
	*/
    bool visible;

	/**
	*  Entity's hitbox
	*/
    FlxRect hitbox;

	/**
	*  Translation of hitbox (to correct collision checking)
	*/
    FlxVector hitboxMove;

	/**
	*  Is entity solid?
	*/
    bool collisions;

	/**
	*  Opacity (in range 0 - 1)
	*/
    float alpha;

	/**
	*  Is this element of interface? If <code>true</code> - don't apply special effects
	*/
    bool isGUI;

	/**
	*  Is object following some path?
	*/
    bool isFollowingPath;

	/**
	*  Linear velocity of path following
	*/
    float followingVelocity;

    /**
    *  Special collision flags. For example FLX_NO_COLLISIONS_UP
    *  will block collision if object's velocity is pointed directly upside.<br />
    *  <b>NOTE: It only works with collide() function, not with overlaps()</b>
    */
    int collisionsFlags;

	/**
	*  Path to follow
	*/
    FlxPath *pathToFollow;

	/**
	*  Get entity's center point
	*  @return Entity's center point
	*/
    FlxVector getCenter();


	/**
	*  Is entity touching object below?
	*  @param floor Object to check
	*  @return <code>true</code> if touching, <code>false</code> if not
	*/
    bool isTouchingFloor(FlxBasic *floor);

	/**
	*  Is entity touching object above?
	*  @param ceil Object to check
	*  @return <code>true</code> if touching, <code>false</code> if not
	*/
    bool isTouchingCeiling(FlxBasic *ceil);

    /**
	*  Check collision between two entities
	*  @param object Entity to check
	*  @param callback Callback. See <code>FlxBasic::CollisionCallback</code>
	*  @return Object which overlaps or <code>NULL</code>
	*/
    virtual FlxBasic* overlaps(FlxBasic *object, const CollisionCallback& callback = nullptr);

    /**
	*  Check collision between two entities and do some physics work
	*  @param object Entity to check
	*  @param callback Callback. See <code>FlxBasic::CollisionCallback</code>
	*  @return Object which overlaps or <code>NULL</code>
	*/
    virtual FlxBasic* collide(FlxBasic *object, const CollisionCallback& callback = nullptr);

	/**
	*  Start following path
	*  @param toFollow Path to follow
	*  @param speed Following velocity
	*/
    void followPath(FlxPath *toFollow, float speed);

	/**
	*  Stop following path
	*/
    void stopFollowing();

	/**
	*  Deactivate entity
	*/
    virtual void kill();

	/**
	*  Default constructor
	*/
    FlxObject();

	/**
	*  Default destructor
	*/
    virtual ~FlxObject();

	/**
	*  Update event template (to override).
	*  Anyway, keep in mind that this implementations should be called in inherited function
	*/
    virtual void update();

	/**
	*  Draw event template (to override)
	*/
    virtual void draw();
};

#endif

