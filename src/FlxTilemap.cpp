#include "FlxTilemap.h"
#include "FlxG.h"

void FlxTilemap::loadMap(int *map, int sizeX, int sizeY, const char *tileset, int tileWidth,
                 int tileHeight, int firstCollidate)
{
    // calculate total size of map
    sizeInPixels.x = tileWidth * sizeX;
    sizeInPixels.y = tileHeight * sizeY;
    bounds.width = sizeInPixels.x;
    bounds.height = sizeInPixels.y;

    // fill map
    int x1 = 0, y1 = 0;
    for(int i = 0; i < sizeX * sizeY; i++) {

        if(map[i] != -1) {
            FlxTile *tile = new FlxTile(x1 * tileWidth, y1 * tileHeight, tileset, tileWidth, tileHeight);

            std::vector<unsigned int> anim;
            anim.push_back(map[i]);
            tile->addAnimation("__default", anim);
            tile->play("__default");

            if(map[i] >= firstCollidate) tile->collidate = true;
            else tile->collidate = false;

            tile->indexX = x1;
            tile->indexY = y1;

            add(tile);
        }

        if(x1 == sizeX - 1) {
            y1++;
            x1 = -1;
        }

        x1++;
    }
}
