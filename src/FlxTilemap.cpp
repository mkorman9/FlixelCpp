#include "FlxTilemap.h"
#include "FlxG.h"

FlxTilemap::FlxTilemap() {
    mapData = 0;
}

FlxTilemap::~FlxTilemap() {
    if(mapData) delete mapData;
}


void FlxTilemap::loadMap(int *map, int sizeX, int sizeY, const char *tileset, int tileWidth,
                 int tileHeight, int firstCollidate)
{
    // calculate total size of map
    size.x = (float)sizeX;
    size.y = (float)sizeY;
    sizeInPixels.x = tileWidth * sizeX;
    sizeInPixels.y = tileHeight * sizeY;
    bounds.width = sizeInPixels.x;
    bounds.height = sizeInPixels.y;

    mapData = new int[sizeX * sizeY];

    // fill map
    int x1 = 0, y1 = 0;
    for(int i = 0; i < sizeX * sizeY; i++) {

        mapData[i] = map[i];

        if(map[i] != -1) {
            FlxTile *tile = new FlxTile(x1 * tileWidth, y1 * tileHeight, tileset, tileWidth, tileHeight);

            tile->addAnimation("__default", { map[i] });
            tile->play("__default");

            if(map[i] >= firstCollidate) tile->collisions = true;
            else tile->collisions = false;

            tile->indexX = x1;
            tile->indexY = y1;
            tile->type = map[i];

            add(tile);
        }

        if(x1 == sizeX - 1) {
            y1++;
            x1 = -1;
        }

        x1++;
    }
}


int FlxTilemap::getTile(int x, int y) {

    if(x < 0 || y < 0 || x >= (int)size.x || y >= (int)size.y) return -1;

    return mapData[x * (int)size.x + y];
}


int FlxTilemap::getTileFromPoint(float pointX, float pointY) {
    int x = pointX / (sizeInPixels.x / size.x);
    int y = pointY / (sizeInPixels.y / size.y);

    return getTile(x, y);
}

void FlxTilemap::setTile(int x, int y, int value) {

    if(x < 0 || y < 0 || x >= (int)size.x || y >= (int)size.y) return;
    mapData[x * (int)size.x + y] = value;
}
