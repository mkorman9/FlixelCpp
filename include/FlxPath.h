/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_PATH_H_
#define _FLX_PATH_H_

#include "backend/cpp.h"

/**
*  Call used by pathfinding functions
*/
class FlxPath {

public:

    /**
	*  Single node structure
	*/
    struct Node {
        float x;
        float y;
    };


    /**
	*  Add new node
	*  @param node Node to add
	*/
    void addNode(const Node& node) {
        nodes.push_back(node);
    }

    /**
	*  Set iterator to front of list
	*/
    void setFront() {
        nodesIterator = nodes.begin();
    }

    /**
	*  Set iterator to end of list
	*/
    void setBack() {
        nodesIterator = nodes.end();
    }

    /**
	*  Get current node and increment iterator
	*  @return Reference to current node
	*/
    Node& getNextNode() {
        return *(nodesIterator++);
    }

    /**
	*  Is iterator at the end of list
	*  @return <code>true</code> if it is, <code>false</code> if it isn't
	*/
    bool isEnd() const {
        return nodesIterator == nodes.end();
    }

private:
    std::list<Node> nodes;
    std::list<Node>::iterator nodesIterator;
};

#endif

