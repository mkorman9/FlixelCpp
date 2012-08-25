/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_G_H_
#define _FLX_G_H_

#include "FlxState.h"
#include "FlxVector.h"
#include "FlxBackendBase.h"
#include "FlxSprite.h"
#include "FlxU.h"
#include "FlxMouse.h"
#include "FlxKeyboard.h"
#include "FlxText.h"
#include "FlxPreloader.h"
#include "FlxSound.h"
#include "FlxMusic.h"
#include "FlxTilemap.h"

/*
*  Main static class which holds all functionality
*/
class FlxG {

public:

    // render surface size
    static int width, height;

    // real screen size
    static int screenWidth, screenHeight;

    // current state
    static FlxState *state;

    // time since last frame
    static float elapsed;

    // backend
    static FlxBackendBase *backend;

    // exit message
    static bool exitMessage;

    // background color
    static int bgColor;

    // keyboard state
    static FlxKeyboard *key;

    // preloader
    static FlxPreloader *preloader;

    // music
    static FlxMusic *music;

    // world's bounds
    static FlxRect worldBounds;

    // scrool vector (read only)
    static FlxVector scroolVector;

    // mouses array pointer
    static std::vector<FlxMouse*> mouse;


    // follow object
    static void followObject(FlxObject *object);

    // set time modifier
    static void setTimeModifier(float mod);

    // setup game
    static int setup(const char *title, int Width, int Height, FlxState *state);

    // plays a specified sound
    static FlxSound play(const char *path, float volume = 1.0f);

    // plays a specified music
    static FlxMusic* playMusic(const char *path, float volume = 1.0f);

    // set current game state
    static void switchState(FlxState *newState);

    // update mouse state (internal)
    static void updateMouses();

private:

    // update state
    static void update();

    // draw state
    static void draw();

    // object to follow
    static FlxObject *toFollow;
};

#endif
