#include "FlxEmitter.h"
#include "backend/BackendHolder.h"
#include "FlxG.h"

// Default particles insertion callback. May be replaced with your own,
// for example inserting Box2D bodies.
extern void FlxDefaultParticleCallback(FlxEmitter *emitter, FlxParticle *particle) {
    emitter->add(particle);
}


// FlxEmitter members start here
FlxEmitter::FlxEmitter(float X, float Y, const FlxVector &speedRangeX, const FlxVector &speedRangeY,
                       const FlxVector &lifeTime, const FlxVector &partRotation,
                       const InsertionCallback& callback)
{
    x = X;
    y = Y;
    particleSpeedX = speedRangeX;
    particleSpeedY = speedRangeY;
    particleRotation = partRotation;
    particleWidth = 0;
    particleHeight = 0;
    particleTiles = 0;
    timeToLife = lifeTime;

    if(callback == nullptr) {
        insertionCallback = FlxDefaultParticleCallback;
    }
    else {
        insertionCallback = callback;
    }
}


FlxEmitter::~FlxEmitter() {
}


void FlxEmitter::at(FlxObject *obj) {
    if(!obj) return;

    x = obj->x;
    y = obj->y;
}


void FlxEmitter::atCenter(FlxObject *obj) {
    if(!obj) return;

    x = obj->x + (obj->width / 2);
    y = obj->y + (obj->height / 2);
}


void FlxEmitter::emit(int howMany) {

    for(int i = 0; i < howMany; i++) {
        FlxParticle *part = new FlxParticle(x, y, tileset.c_str(), particleWidth, particleHeight,
                                            FlxU::random(0, particleTiles));

        part->acceleration.y = gravity;
        part->angle = FlxU::random((int)particleRotation.x, (int)particleRotation.y);
        part->velocity.x = FlxU::random((int)particleSpeedX.x, (int)particleSpeedX.y);
        part->velocity.y = FlxU::random((int)particleSpeedY.x, (int)particleSpeedY.y);

        if(timeToLife.x > 0 && timeToLife.y > 0)
            part->timeToLife = FlxU::random(timeToLife.x, timeToLife.y);
        else
            part->timeToLife = -1.f;

        insertionCallback(this, part);
    }
}


void FlxEmitter::loadGraphic(const char *Tileset, int Width, int Height, int TileTypes) {
    tileset = Tileset;
    particleWidth = Width;
    particleHeight = Height;
    particleTiles = TileTypes;
}


void FlxEmitter::update() {

    for(unsigned int i = 0; i < members.size(); i++) {
        FlxParticle *part = (FlxParticle*)members[i];
        if(part->timeToLife == -1.f) continue;

        if(part->timeToLife <= 0) {
            remove(part);
            continue;
        }

        part->timeToLife -= FlxG::fixedTime;
    }

    FlxGroup::update();
}


void FlxEmitter::draw() {
    FlxGroup::draw();
}
