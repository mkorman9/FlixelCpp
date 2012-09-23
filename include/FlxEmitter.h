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

/*
*  Particle emitter
*/
class FlxEmitter : public FlxGroup {

private:
    std::string tileset;
public:

    typedef std::function<void(FlxEmitter*, FlxParticle*)> InsertionCallback;


    // position of emitter
    float x, y;

    // gravity acceleration
    float gravity;

    // particle direction range in X axis
    FlxVector particleSpeedX;

    // particle direction range in Y axis
    FlxVector particleSpeedY;

    // particle rotation range
    FlxVector particleRotation;

    // time to life range
    FlxVector timeToLife;

    // particle width
    int particleWidth;

    // particle height
    int particleHeight;

    // number of available tiles for particle
    int particleTiles;


    // constructor
    FlxEmitter(float X, float Y, const FlxVector &speedRangeX, const FlxVector &speedRangeY,
               const FlxVector &life, const FlxVector &partRotation = FlxVector(0, 2*FlxU::PI),
               const InsertionCallback& callback = nullptr);

    // destructor
    virtual ~FlxEmitter();

    // set position of emitter to the position of object
    void at(FlxObject *obj);

    // set position of emitter to the center of object
    void atCenter(FlxObject *obj);

    // load particles graphic
    void loadGraphic(const char *tileset, int width, int height, int tileTypes = 1);

    // emit specified amount of particles
    void emit(int howMany);

    virtual void update();
    virtual void draw();

private:
    InsertionCallback insertionCallback;
};

#endif




