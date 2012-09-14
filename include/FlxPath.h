/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_PATH_H_
#define _FLX_PATH_H_

#include "backend/cpp.h"

/*
*  Path class
*/
class FlxPath {

public:

    // single node structure
    struct Node {
        int x;
        int y;
    };


    // add new node
    void addNode(const Node& node) {
        nodes.push_back(node);
    }

    // set iterator to front of nodes list
    void setFront() {
        nodesIterator = nodes.begin();
    }

    // set iterator to end of nodes list
    void setBack() {
        nodesIterator = nodes.end();
    }

    // get next node
    Node& getNextNode() {
        return *(nodesIterator++);
    }

    // is iterator on the end of list
    bool isEnd() const {
        return nodesIterator == nodes.end();
    }

private:
    std::list<Node> nodes;
    std::list<Node>::iterator nodesIterator;
};

#endif

