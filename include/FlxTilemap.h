/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_TILEMAP_H_
#define _FLX_TILEMAP_H_

#include "FlxTile.h"
#include "FlxGroup.h"
#include "FlxPath.h"

/**
*  Basic map class
*/
class FlxTilemap : public FlxGroup {

public:

	/**
	*  Insertion callback. Similar to <code>FlxEmitter::InsertionCallback</code>
	*/
    typedef std::function<void(FlxTilemap*, FlxTile*)> InsertionCallback;

    /** 
	*  Raw map data. Index list in row order.
	*/
    int *mapData;

    /** 
	*  Bounds of the map (in pixels).
	*  Used on scrooling
	*/
    FlxRect bounds;

    /** 
	*  Total map size (in tiles)
	*/
    FlxVector size;

    /** 
	*  Total map size (in pixels)
	*/
    FlxVector sizeInPixels;

    /** 
	*  Index of first collidable tile in tileset
	*/
    int firstSolid;


    /** 
	*  Default constructor
	*  @param callback See <code>FlxTilemap::InsertionCallback</code>
	*/
    FlxTilemap(const InsertionCallback& callback = nullptr);

    /** 
	*  Default destructor
	*/
    virtual ~FlxTilemap();

    /** 
	*  Loads map to memory
	*  @param map Raw inices array in row order
	*  @param sizeX Width of map in tiles
	*  @param sizeY Height of map in tiles
	*  @param tileset Path to tileset file (must be in local device's storage)
	*  @param tileWidth Single tile width (in pixels)
	*  @param tileHeight Single tile height (in pixels)
	*  @param firstCollide Index of first collidable tile in tileset
	*/
    void loadMap(int *map, int sizeX, int sizeY, const char *tileset, int tileWidth,
                 int tileHeight, int firstCollide = 1);

    /** 
	*  Get tile index from specified point (in tiles)
	*  @param x Tile X
	*  @param y Tile Y
	*  @return Tile index or -1 on failure
	*/
    int getTile(int x, int y);

    /** 
	*  Get tile index from specified pixel
	*  @param pointX Pixel X
	*  @param pointY Pixel Y
	*  @return Tile index or -1 on failure
	*/
    int getTileFromPoint(float pointX, float pointY);

    /** 
	*  Set new index to tile from specified point 
	*  @param x Tile X
	*  @param y Tile Y
	*  @param value New index of tile
	*/
    void setTile(int x, int y, int value);

	/** 
	*  Find path from start to end point.
	*  NOTE: Always returns NULL if <code>FLX_NO_PATHFINDING</code> is present
	*  @param startX Start tile X
	*  @param startY Start tile Y
	*  @param endX End tile X
	*  @param endY End tile Y
	*  @return List of points (in pixels!) to cross, or NULL if path was not found 
	*/
    FlxPath* findPath(int startX, int startY, int endX, int endY);

	/** 
	*  Update event (to override)
	*/
    virtual void update() {
        FlxGroup::update();
    }

	/** 
	*  Draw event (to override)
	*/
    virtual void draw() {
        FlxGroup::draw();
    }

private:
    InsertionCallback insertionCallback;
};

#endif


