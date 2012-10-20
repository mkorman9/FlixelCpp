/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_GROUP_H_
#define _FLX_GROUP_H_

#include "backend/cpp.h"
#include "FlxBasic.h"


class FlxObject;


/**
*  Collection of game entities (objects or other groups)
*/
class FlxGroup : public FlxBasic {

public:

    /**
	*  Members of group
	*/
    std::vector<FlxBasic*> members;

	/**
	*  Pair of two entities. Used in <code>selfOverlaps</code> and <code>selfCollide</code> 
	*/
    struct EntitiesSet {
        FlxBasic *first;
        FlxBasic *second;
    };

	
    /**
	*  Default constructor
	*/
    FlxGroup();

    /**
	*  Virtual destructor
	*/
    virtual ~FlxGroup();

    /**
	*  Add new entity to group.
	*  @param object Entity to add (musn't be NULL)
	*  @return <code>object</code> for chaining
	*/
    FlxBasic* add(FlxBasic *object);

    /**
	*  Remove entity from group and <code>delete</code> it
	*  @param object Entity to remove
	*  @param dontDelete Put <code>true</code> here if you wouldn't delete object after removement
	*  @return <code>true</code> if removement was successful. <code>false</code> if entity was not found in group
	*/
    bool remove(FlxBasic *object, bool dontDelete = false);

    /**
	*  Remove all enitites from group and delete it's memory
	*/
    void clear();

    /**
	*  Get members count
	*  @return Elements count
	*/
    unsigned int size();

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
	*  Check collision between two entities inside the same group
	*  @param callback Callback. See <code>FlxBasic::CollisionCallback</code>
	*  @return Set of two elements which overlaps
	*/
    EntitiesSet selfOverlaps(const CollisionCallback& callback = nullptr);

    /**
	*  Check collision between two entities inside the same group and do some physics work
	*  @param callback Callback. See <code>FlxBasic::CollisionCallback</code>
	*  @return Set of two elements which overlaps
	*/
    EntitiesSet selfCollide(const CollisionCallback& callback = nullptr);

	/**
	*  Update event.
	*/
    virtual void update();
	
	/**
	*  Draw all elements flagged as GUI
	*/
    virtual void drawGUI();
	
	/**
	*  Draw all elements flagged as non-GUI
	*/
    virtual void draw();


    // inline stuff for script engine
    inline bool _isObject(int id) { return members[id]->entityType == FLX_OBJECT; }
    inline bool _isGroup(int id) { return members[id]->entityType == FLX_GROUP; }
    inline FlxObject* _getObject(int id) { return (FlxObject*) members[id]; }
    inline FlxGroup* _getGroup(int id) { return (FlxGroup*) members[id]; }
};

#endif
