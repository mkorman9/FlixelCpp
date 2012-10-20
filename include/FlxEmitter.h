/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_EMITTER_H_
#define _FLX_EMITTER_H_

#include "FlxGroup.h"
#include "FlxObject.h"
#include "FlxVector.h"
#include "FlxU.h"
#include "FlxParticle.h"

/**
*  Particle emitter
*/
class FlxEmitter : public FlxGroup {

private:
    std::string tileset;
public:

	/**
	*  New particle insertion callback. It's helpful when you want to integrate external physics engine.
	*/
    typedef std::function<void(FlxEmitter*, FlxParticle*)> InsertionCallback;


    /**
	*  X postion of the emmiter
	*/
    float x;
	
	/**
	*  Y postion of the emmiter
	*/
	float y;

	/**
	*  Particles vertical acceleration
	*/
    float gravity;

	/**
	*  Range of particles speed in X-axis (it's not a vector, it's a range)
	*/
    FlxVector particleSpeedX;

	/**
	*  Range of particles speed in Y-axis (it's not a vector, it's a range)
	*/
    FlxVector particleSpeedY;

	/**
	*  Range of particles angle in radians (it's not a vector, it's a range)
	*/
    FlxVector particleRotation;

	/**
	*  Range of particles lifetime in seconds (it's not a vector, it's a range)
	*/
    FlxVector timeToLife;

	/**
	*  Single particle width
	*/
    int particleWidth;

	/**
	*  Single particle height
	*/
    int particleHeight;

	/**
	*  Number of different tile types to random from tilemap
	*/
    int particleTiles;


    /**
	*  @param X x-postions oif the emmiter
	*  @param Y y-postions oif the emmiter
	*  @param speedRangeX Range of particles speed in X-axis
	*  @param speedRangeY Range of particles speed in Y-axis
	*  @param life Range of particles lifetime in seconds
	*  @param partRotation Range of particles angle in radians
	*  @param callback Insertion callback, see <code>InsertionCallback</code>
	*/
    FlxEmitter(float X, float Y, const FlxVector &speedRangeX, const FlxVector &speedRangeY,
               const FlxVector &life, const FlxVector &partRotation = FlxVector(0, 2*FlxU::PI),
               const InsertionCallback& callback = nullptr);

    /**
	*  Virtual destructor
	*/
    virtual ~FlxEmitter();

    /**
	*  Set emitter's position to passed object positon
	*  @param obj Object to set
	*/
    void at(FlxObject *obj);

    /**
	*  Set emitter's position to center of passed object
	*  @param obj Object to set
	*/
    void atCenter(FlxObject *obj);

    /**
	*  Load tilemap for particles
	*  @param tileset Image to load (must be in device's internal storage)
`	*  @param width Width of single particle	
	*  @param height Height of single particle
	*  @param tileTypes How many different types of particles can be generated from specified tileset
	*/
    void loadGraphic(const char *tileset, int width, int height, int tileTypes = 1);

    /**
	*  Emmit specified amount of particles
	*  @param howMany How many particles
	*/
    void emit(int howMany);

	/**
	*  Overrided update event
	*/
    virtual void update();
	
	/**
	*  Overrided draw event
	*/
    virtual void draw();

private:
    InsertionCallback insertionCallback;
};

#endif




