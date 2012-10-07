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
#include "FlxSave.h"
#include "FlxButton.h"
#include "FlxEmitter.h"
#include "FlxHttpRequest.h"
#include "FlxMouseHolder.h"
#include "FlxShader.h"
#include "FlxVirtualKeyboard.h"
#include "FlxPath.h"
#include "FlxScript.h"

#include "tweener/CppTween.h"


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

    // fixed timestep time
    static float fixedTime;

    // total application time
    static float totalTime;

    // time since last frame
    static float elapsed;

    // time in seconds since last frame
    static float fps;

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

	// scrooling vector
	static FlxVector scroolVector;

    // mouses array pointer
    static std::vector<FlxMouse*> mousesList;

    // mouse abstraction layer
    static FlxMouseHolder mouse;

    // is screen being flashed
    static bool flashing;

    // tweener object
    static tween::Tweener tweener;

    // shaders to draw
    static FlxShadersList shaders;

    // global script engine
    static FlxScriptEngine *scriptEngine;

    // global utility scripts
    static FlxScriptsList scripts;


    // follow object
    static void followObject(FlxObject *object);

    // setup game
    static int setup(const char *title, int Width, int Height, FlxState *state,
                     const char *icon = NULL);

    // plays a specified sound
    static FlxSound play(const char *path, float volume = 1.0f);

    // plays a specified music
    static FlxMusic* playMusic(const char *path, float volume = 1.0f);

    // set current game state
    static void switchState(FlxState *newState);

    // update mouse state (internal)
    static void updateMouses();

    // special camera effect - flash screen
    static void flash(int color, float time);

    // check objects collision
    static FlxBasic* overlaps(FlxBasic *one, FlxBasic *two, const FlxBasic::CollisionCallback&
                         collisionCallback = nullptr);

    // check objects collision and do some physics work
    static FlxBasic* collide(FlxBasic *one, FlxBasic *two, const FlxBasic::CollisionCallback&
                         collisionCallback = nullptr);


    // update game state (internal)
    static void innerUpdate();

    // draw game data (internal)
    static void innerDraw();

private:

    // object to follow
    static FlxObject *toFollow;

    // fps stuff
    static float fpsCounter;

    // state to switch next frame
    static FlxState *stateToSwitch;

    // flash screen effect stuff
    static FlxSprite flashSprite;
    static float flashCounter, flashMaxTime;
};

#endif
