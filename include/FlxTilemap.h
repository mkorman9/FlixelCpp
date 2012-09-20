/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_TILEMAP_H_
#define _FLX_TILEMAP_H_

#include "FlxTile.h"
#include "FlxGroup.h"
#include "FlxPath.h"

/*
*  Basic map class
*/
class FlxTilemap : public FlxGroup {

public:

    typedef std::function<void(FlxTilemap*, FlxTile*)> InsertionCallback;

    // raw map data
    int *mapData;

    // bounds of the map (in pixels)
    FlxRect bounds;

    // total map size
    FlxVector size;

    // total size of map (in pixels)
    FlxVector sizeInPixels;

    // first solid tile index
    int firstSolid;


    // constructor
    FlxTilemap(const InsertionCallback& callback = nullptr);

    // destructor
    ~FlxTilemap();

    // load map to memory
    void loadMap(int *map, int sizeX, int sizeY, const char *tileset, int tileWidth,
                 int tileHeight, int firstCollide = 1);

    // get tile type from specified index
    int getTile(int x, int y);

    // get tile by point
    int getTileFromPoint(float pointX, float pointY);

    // set tile on index
    void setTile(int x, int y, int value);

    // find path from start point to end point.
    // return NULL if it's unavailable
    FlxPath* findPath(int startX, int startY, int endX, int endY);

    virtual void update() {
        FlxGroup::update();
    }

    virtual void draw() {
        FlxGroup::draw();
    }

private:
    InsertionCallback insertionCallback;
};

#endif


