#include "FlxTilemap.h"
#include "FlxG.h"

#ifndef FLX_NO_PATHFINDING
    #include "astar/stlastar.h"
    #include "PathFinder.inl"
#endif


// Default tile insertion callback. May be replaced with your own,
// for example inserting Box2D bodies.
extern void FlxDefaultTileCallback(FlxTilemap *map, FlxTile *tile) {
    map->add(tile);
}


// FlxTilemap members start here
FlxTilemap::FlxTilemap(const InsertionCallback& callback) {
    mapData = NULL;

    if(callback == nullptr) {
        insertionCallback = FlxDefaultTileCallback;
    }
    else {
        insertionCallback = callback;
    }
}


FlxTilemap::~FlxTilemap() {
    if(mapData) delete[] mapData;
}


void FlxTilemap::loadMap(int *map, int sizeX, int sizeY, const char *tileset, int tileWidth,
                 int tileHeight, int firstCollide)
{
    // calculate total size of map
    size.x = static_cast<float>(sizeX);
    size.y = static_cast<float>(sizeY);
    sizeInPixels.x = static_cast<float>(tileWidth * sizeX);
    sizeInPixels.y = static_cast<float>(tileHeight * sizeY);
    bounds.width = static_cast<int>(sizeInPixels.x);
    bounds.height = static_cast<int>(sizeInPixels.y);
    firstSolid = firstCollide;

    mapData = new int[sizeX * sizeY];

    // copy tiles to map data
    for(int i = 0; i < sizeX * sizeY; i++) {
        mapData[i] = map[i];
    }

    // fill map data
    int x = 0, y = 0;
    for(int i = 0; i < sizeX * sizeY; i++) {

        if(mapData[i] != -1) {
            FlxTile *tile = new FlxTile(static_cast<float>(x * tileWidth),
										static_cast<float>(y * tileHeight), tileset, tileWidth, tileHeight);

            tile->addAnimation("__default", FlxInitializerList<unsigned int>(mapData[i]));
            tile->play("__default");

            tile->collisions = (mapData[i] >= firstSolid);
            tile->indexX = x;
            tile->indexY = y;
            tile->type = mapData[i];

            insertionCallback(this, tile);
        }

        if(x == sizeX - 1) {
            y++;
            x = -1;
        }

        x++;
    }
}


int FlxTilemap::getTile(int x, int y) {

    if(x < 0 || y < 0 || x >= (int)size.x || y >= (int)size.y) return -1;

    return mapData[(y * (int)size.x) + x];
}


int FlxTilemap::getTileFromPoint(float pointX, float pointY) {
    int x = static_cast<int>(pointX / (sizeInPixels.x / size.x));
    int y = static_cast<int>(pointY / (sizeInPixels.y / size.y));

    return getTile(x, y);
}


void FlxTilemap::setTile(int x, int y, int value) {

    if(x < 0 || y < 0 || x >= (int)size.x || y >= (int)size.y) return;
    mapData[(y * (int)size.x) + x] = value;
}


void FlxTilemap::setTilesProperty(int index, int flags) {

    for(unsigned int i = 0; i < members.size(); i++) {
        FlxTile *tile = (FlxTile*) members[i];

        if(tile->type == index) {
            tile->collisionsFlags = flags;
        }
    }
}


FlxPath* FlxTilemap::findPath(int startX, int startY, int endX, int endY) {

    #ifndef FLX_NO_PATHFINDING

    // initialize path searching
    AStarSearch<MapSearchNode> astarsearch;

    MapSearchNode nodeStart(mapData, (int)size.x, (int)size.y, firstSolid);
	nodeStart.x = startX;
	nodeStart.y = startY;

	MapSearchNode nodeEnd(mapData, (int)size.x, (int)size.y, firstSolid);
	nodeEnd.x = endX;
	nodeEnd.y = endY;

	astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);
	unsigned int step = 0;

	// find path
	do {
        step = astarsearch.SearchStep();
	}
	while(step == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

	// save results
    if(step == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED) {
		MapSearchNode *node = astarsearch.GetSolutionStart();
        FlxPath *path = new FlxPath();

        FlxPath::Node n = { node->x * (sizeInPixels.x / size.x), node->y * (sizeInPixels.x / size.x) };
        path->addNode(n);

		while(true) {
			node = astarsearch.GetSolutionNext();
			if(!node) break;

            n.x = node->x * (sizeInPixels.x / size.x);
            n.y = node->y * (sizeInPixels.x / size.x);
            path->addNode(n);
		}

		astarsearch.FreeSolutionNodes();
		return path;
	}

    #endif

	return NULL; // path not found
}

