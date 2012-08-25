/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_TILE_H_
#define _FLX_TILE_H_

#include "FlxSprite.h"

class FlxTile : public FlxSprite {

public:

    int indexX;
    int indexY;
    int type;

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

