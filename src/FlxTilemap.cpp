#include "FlxTilemap.h"
#include "FlxG.h"

#ifndef FLX_NO_PATHFINDING
    #include "astar/stlastar.h"
    #include "PathFinder.inl"
#endif


// Default tile insertion callbac. May be replaced with your own,
// for example inserting Box2D bodies.
void defaultTileCallback(FlxTilemap *map, int value, int indexX, int indexY,
                         int width, int height, bool collisions, const char *tileset)
{
    FlxTile *tile = new FlxTile(indexX * width, indexY * height, tileset, width, height);

    tile->addAnimation("__default", { value });
    tile->play("__default");

    tile->collisions = collisions;
    tile->indexX = indexX;
    tile->indexY = indexY;
    tile->type = value;

    map->add(tile);
}


// FlxTilemap members start here
FlxTilemap::FlxTilemap(const InsertionCallback& callback) {
    mapData = NULL;

    if(callback == nullptr) {
        insertionCallback = defaultTileCallback;
    }
    else {
        insertionCallback = callback;
    }
}

FlxTilemap::~FlxTilemap() {
    if(mapData) delete mapData;
}


void FlxTilemap::loadMap(int *map, int sizeX, int sizeY, const char *tileset, int tileWidth,
                 int tileHeight, int firstCollide)
{
    // calculate total size of map
    size.x = (float)sizeX;
    size.y = (float)sizeY;
    sizeInPixels.x = tileWidth * sizeX;
    sizeInPixels.y = tileHeight * sizeY;
    bounds.width = sizeInPixels.x;
    bounds.height = sizeInPixels.y;
    firstSolid = firstCollide;

    mapData = new int[sizeX * sizeY];

    // fill map
    int x1 = 0, y1 = 0;
    for(int i = 0; i < sizeX * sizeY; i++) {

        mapData[i] = map[i];

        if(map[i] != -1) {
            insertionCallback(this, map[i], x1, y1, tileWidth, tileHeight,
                              (map[i] >= firstSolid), tileset);
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

    return mapData[y * (int)size.x + x];
}


int FlxTilemap::getTileFromPoint(float pointX, float pointY) {
    int x = pointX / (sizeInPixels.x / size.x);
    int y = pointY / (sizeInPixels.y / size.y);

    return getTile(x, y);
}


void FlxTilemap::setTile(int x, int y, int value) {

    if(x < 0 || y < 0 || x >= (int)size.x || y >= (int)size.y) return;
    mapData[y * (int)size.x + x] = value;
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

