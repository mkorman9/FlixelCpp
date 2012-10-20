/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_TILE_H_
#define _FLX_TILE_H_

#include "FlxSprite.h"

/**
*  Single tile class
*/
class FlxTile : public FlxSprite {

public:

	/**
	*  Tile index in X-axis
	*/
    int indexX;
	
	/**
	*  Tile index in Y-axis
	*/
    int indexY;
	
	/**
	*  Tile type index
	*/
    int type;
	
	/**
	*  Default constructor
	*  @param X Position in X-axis
	*  @param Y Position in Y-axis
	*  @param gfx Path to tileset (must be in local device's storage)
	*  @param Width Tile width
	*  @param Height Tile height
	*/
    FlxTile(float X = 0, float Y = 0, const char *gfx = 0, int Width = 0, int Height = 0) {

        indexX = indexY = 0;
        type = 0;

        x = X;
        y = Y;

        reset();

        if(gfx) loadGraphic(gfx, Width, Height);
    }
};

#endif

