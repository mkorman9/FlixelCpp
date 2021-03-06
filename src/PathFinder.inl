class MapSearchNode {

public:

    int x;
    int y;
	int *Map;
	int Width;
	int Height;
	int FirstCollide;

	MapSearchNode() {
	}

	MapSearchNode(int *map, int width, int height, int firstCollide) {
		x = y = 0;
		Map = map;
		Width = width;
		Height = height;
		FirstCollide = firstCollide;
	}

	int getMap(int X, int Y) {
		if(X < 0 || Y < 0 || X >= Width || Y >= Height) return (int)FirstCollide;
		return (int) Map[Y * Width + X];
	}

	bool IsSameState(MapSearchNode &rhs) {
		return (x == rhs.x) && (y == rhs.y);
	}

	float GoalDistanceEstimate(MapSearchNode &nodeGoal) {
		float xd = fabs(float(((float)x - (float)nodeGoal.x)));
		float yd = fabs(float(((float)y - (float)nodeGoal.y)));

		return xd + yd;
	}

	bool IsGoal(MapSearchNode &nodeGoal) {
		return ((x == nodeGoal.x) && (y == nodeGoal.y));
	}

	float GetCost(MapSearchNode &successor) {
	    (void)successor;
		return (float) getMap(x, y);
	}

	bool GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node) {

		int parent_x = -1;
		int parent_y = -1;

		if(parent_node) {
			parent_x = parent_node->x;
			parent_y = parent_node->y;
		}

		MapSearchNode NewNode;

		if((getMap(x - 1, y) < FirstCollide) && !((parent_x == x - 1) && (parent_y == y))) {
			NewNode = MapSearchNode(Map, Width, Height, FirstCollide);
			NewNode.x = x - 1;
			NewNode.y = y;
			astarsearch->AddSuccessor(NewNode);
		}

		if((getMap(x, y - 1) < FirstCollide) && !((parent_x == x) && (parent_y == y - 1))) {
			NewNode = MapSearchNode(Map, Width, Height, FirstCollide);
			NewNode.x = x;
			NewNode.y = y - 1;
			astarsearch->AddSuccessor(NewNode);
		}

		if((getMap(x + 1, y) < FirstCollide) && !((parent_x == x + 1) && (parent_y == y))) {
			NewNode = MapSearchNode(Map, Width, Height, FirstCollide);
			NewNode.x = x + 1;
			NewNode.y = y;
			astarsearch->AddSuccessor(NewNode);
		}


		if((getMap(x, y + 1) < FirstCollide) && !((parent_x == x) && (parent_y == y + 1))) {
			NewNode = MapSearchNode(Map, Width, Height, FirstCollide);
			NewNode.x = x;
			NewNode.y = y + 1;
			astarsearch->AddSuccessor(NewNode);
		}

		return true;
	}
};
