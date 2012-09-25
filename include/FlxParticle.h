/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_PARTICLE_H_
#define _FLX_PARTICLE_H_

#include "FlxSprite.h"

class FlxParticle : public FlxSprite {

public:

    float timeToLife;

    FlxParticle(float X = 0, float Y = 0, const char *gfx = 0, int Width = 0, int Height = 0, int tile = 0) {

        x = X;
        y = Y;
        timeToLife = 0;

        reset();

        if(gfx) {
            loadGraphic(gfx, Width, Height);

            addAnimation("default", FlxInitializerList<unsigned int>(tile));
            play("default");
        }
    }
};

#endif


