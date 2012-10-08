/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_GROUP_H_
#define _FLX_GROUP_H_

#include "backend/cpp.h"
#include "FlxBasic.h"


class FlxObject;


/*
*  Collection of game objects
*/
class FlxGroup : public FlxBasic {

public:
    std::vector<FlxBasic*> members;

    struct EntitiesSet {
        FlxBasic *first;
        FlxBasic *second;
    };

    // constructor
    FlxGroup();

    // destructor
    virtual ~FlxGroup();

    // add new entity to group. Returns new object (for chaining)
    FlxBasic* add(FlxBasic *object);

    // remove entity from group
    bool remove(FlxBasic *object, bool dontDelete = false);

    // remove all elements from group and free memory
    void clear();

    // get entities count
    unsigned int size();

    // any of elements collidates with something
    virtual FlxBasic* overlaps(FlxBasic *object, const CollisionCallback& callback = nullptr);

    // check overlap and do some phycics work
    virtual FlxBasic* collide(FlxBasic *object, const CollisionCallback& callback = nullptr);

    // check collisions with each other group member
    EntitiesSet selfOverlaps(const CollisionCallback& callback = nullptr);

    // check collisions with each other group member and do some phycics work
    EntitiesSet selfCollide(const CollisionCallback& callback = nullptr);

    virtual void update();
    virtual void drawGUI();
    virtual void draw();


    // inline stuff for script engine
    inline bool _isObject(int id) { return members[id]->entityType == FLX_OBJECT; }
    inline bool _isGroup(int id) { return members[id]->entityType == FLX_GROUP; }
    inline FlxObject* _getObject(int id) { return (FlxObject*) members[id]; }
    inline FlxGroup* _getGroup(int id) { return (FlxGroup*) members[id]; }
};

#endif
