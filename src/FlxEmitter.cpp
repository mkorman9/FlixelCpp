#include "FlxEmitter.h"
#include "backend/BackendHolder.h"
#include "FlxG.h"

FlxEmitter::FlxEmitter(float X, float Y, const FlxVector &speedRangeX, const FlxVector &speedRangeY,
                       const FlxVector &lifeTime, const FlxVector &partRotation)
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
        part->timeToLife = FlxU::random(timeToLife.x, timeToLife.y);

        add(part);
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
