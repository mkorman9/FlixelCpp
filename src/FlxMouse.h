/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_MOUSE_H_
#define _FLX_MOUSE_H_

/*
*  Mouse handler
*/
struct FlxMouse {

private:
    bool lastLeftDown, lastRightDown, lastMiddleDown;
public:
    bool leftDown, middleDown, rightDown;
    bool leftPressed, middlePressed, rightPressed;
    bool leftReleased, middleReleased, rightReleased;

    float x;
    float y;

    int index;


    FlxMouse(int id);
    void show();
    void hide();

    void updateState();
};

#endif

