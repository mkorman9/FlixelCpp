/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_PARTICLE_H_
#define _FLX_PARTICLE_H_

#include "FlxSprite.h"

/**
*  Single particle representation
*/
class FlxParticle : public FlxSprite {

public:

	/**
	*  Duration of particle's life (in seconds)
	*/
    float timeToLife;
	
	
	/**
	*  Default constructor
	*  @param X Position of particle in X-axis
	*  @param Y Position of particle in Y-axis
	*  @param gfx Path to tileset (must be in local device's storage)
	*  @param Width Width of single particle
	*  @param Height Height of single particle
	*  @param tile Tile index
	*/
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


