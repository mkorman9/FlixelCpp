/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_TILEMAP_H_
#define _FLX_TILEMAP_H_

#include "FlxTile.h"
#include "FlxGroup.h"

/*
*  Basic map class
*/
class FlxTilemap : public FlxGroup {

public:

    // bounds of the map (in pixels)
    FlxRect bounds;

    // total size of map (in pixels)
    FlxVector sizeInPixels;


    // load map to memory
    void loadMap(int *map, int sizeX, int sizeY, const char *tileset, int tileWidth,
                 int tileHeight, int firstCollidate = 1);

    virtual void update() {
        FlxGroup::update();
    }

    virtual void draw() {
        FlxGroup::draw();
    }
};

#endif


