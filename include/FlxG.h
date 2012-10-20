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


/**
*  Main class which holds all functionality
*/
class FlxG {

public:

    /**
	*  Render surface width.
	*/
    static int width;
	
	/**
	*  Render surface height.
	*/
	static int height;

    /**
	*  Desktop resolution in X-axis
	*/
    static int screenWidth;
	
	/**
	*  Desktop resolution in Y-axis
	*/
	static int screenHeight;

    /**
	*  Current state
	*/
    static FlxState *state;

    /**
	*  Fixed timestep duration (in seconds)
	*/
    static float fixedTime;

    /**
	*  Total time of application existance (in seconds)
	*/
    static float totalTime;

    /**
	*  Time since last frame (in seconds)
	*/
    static float elapsed;

    /**
	*  Frames per second
	*/
    static float fps;

    /**
	*  Framework backend
	*/
    static FlxBackendBase *backend;

    /**
	*  Set it true if application should end
	*/
    static bool exitMessage;

    /**
	*  Background color
	*/
    static int bgColor;

    /**
	*  Current keyboard state
	*/
    static FlxKeyboard *key;

    /**
	*  Preloader
	*/
    static FlxPreloader *preloader;

    /**
	*  Current music started by <code>playMusic()</code>
	*/
    static FlxMusic *music;

    /**
	*  Scrooling bounds
	*/
    static FlxRect worldBounds;

	/**
	*  Scrooling vector
	*/
	static FlxVector scroolVector;

    /**
	*  Mouses (touches) list
	*/
    static std::vector<FlxMouse*> mousesList;

    /**
	*  Helpful mouse abstraction interface
	*/
    static FlxMouseHolder mouse;

    /**
	*  Is screen being flashed?
	*/
    static bool flashing;

    /**
	*  Main tweener reference
	*/
    static tween::Tweener tweener;

    /**
	*  Active shaders list
	*/
    static FlxShadersList shaders;

    /**
	*  Pointer to default scripting engine
	*/
    static FlxScriptEngine *scriptEngine;

    /**
	*  Active scripts list
	*/
    static FlxScriptsList globalScripts;


    /**
	*  Follow some object with camera
	*  @param object Object to follow
	*/
    static void followObject(FlxObject *object);

    /**
	*  Setup framework
	*  @param title Window title (ASCII format)
	*  @param Width Window width
	*  @param Height Window height
	*  @param state Default state
	*  @param icon Aplication icon path (in local storage)
	*  @return Application result (0 on success, > 0 on error)
	*/
    static int setup(const char *title, int Width, int Height, FlxState *state,
                     const char *icon = NULL);

    /**
	*  Play specified sound.
	*  @param path Path to sound file (in local storage)
	*  @param volume Sound volume (in range 0.0 - 1.0)
	*  @return Reference to sound object
	*/
    static FlxSound play(const char *path, float volume = 1.0f);

    /**
	*  Play specified music.
	*  @param path Path to music file (in local storage)
	*  @param volume Music volume (in range 0.0 - 1.0)
	*  @return Pointer to music object
	*/
    static FlxMusic* playMusic(const char *path, float volume = 1.0f);

    /**
	*  Set new application state (NOTE: it will be done in <b>NEXT</b> frame)
	*  @param newState State to switch
	*/
    static void switchState(FlxState *newState);

    /**
	*  Update touch devices (Internal. Do not touch!)
	*/
    static void updateMouses();

    /**
	*  Camera effect. Screen flash.
	*  @param Color to flash
	*  @param time Time of flash (in seconds)
	*/
    static void flash(int color, float time);

    /**
	*  Check collision between two entities
	*  @param one First entity
	*  @param two Second entity
	*  @param collisionCallback Callback. See <code>FlxBasic::CollisionCallback</code>
	*  @return Object which overlaps (taken from second entity)
	*/
    static FlxBasic* overlaps(FlxBasic *one, FlxBasic *two, const FlxBasic::CollisionCallback&
                         collisionCallback = nullptr);

    /**
	*  Check collision between two entities and do some physics work
	*  @param one First entity
	*  @param two Second entity
	*  @param collisionCallback Callback. See <code>FlxBasic::CollisionCallback</code>
	*  @return Object which overlaps (taken from second entity)
	*/
    static FlxBasic* collide(FlxBasic *one, FlxBasic *two, const FlxBasic::CollisionCallback&
                         collisionCallback = nullptr);


    /**
	*  Update application state (Internal! Do not touch!)
	*/
    static void innerUpdate();

    /**
	*  Draw application's stuff (Internal! Do not touch!)
	*/
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
