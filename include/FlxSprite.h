/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_SPRITE_H_
#define _FLX_SPRITE_H_

#include "FlxObject.h"
#include "FlxBackendBase.h"
#include "FlxAnim.h"

/**
*  Class represents drawable and animated graphic object
*/
class FlxSprite : public FlxObject {

protected:
    FlxBackendImage *graphic;
    int sourceX, sourceY;
    int currentFrame, currentFrameNumber;
    FlxAnim *currentAnimation;
    std::vector<FlxAnim*> animations;
    float frameCounter;

    void calcFrame();
    void updateAnimation();
public:

    /**
	*  Is sprite flipped horizontaly
	*/
    bool flipped;

    /**
	*  Is animation finished?
	*/
    bool animationFinished;


    /**
	*  Default constructor
	*  @param x Position in X-axis
	*  @param y Position in Y-axis
	*  @param gfx Path to tileset file (must be in local device's storage)
	*  @param Width Width of single frame (set 0 if you want full image size)
	*  @param Height Height of single frame (set 0 if you want full image size)
	*/
    FlxSprite(float x = 0, float y = 0, const char *gfx = NULL, int Width = 0, int Height = 0);

    /**
	*  Default destructor
	*/
    virtual ~FlxSprite();

    /**
	*  Reset all sprite data
	*/
    void reset();

    /**
	*  Load image to memory
	*  @param gfx Path to tileset file (must be in local device's storage)
	*  @param Width Width of single frame (set 0 if you want full image size)
	*  @param Height Height of single frame (set 0 if you want full image size)
	*  @return Loading result
	*/
    bool loadGraphic(const char *gfx, int Width = 0, int Height = 0);

    /**
	*  Create image in memory
	*  @param width Width of image
	*  @param height Height of image
	*  @param color Color of texture (24-bit format without alpha)
	*/
    void makeGraphic(int width, int height, int color);

    /**
	*  Add new animation state
	*  @param name State's name
	*  @param frames Frames list
	*  @param time Duration of single frame (in seconds)
	*  @param Should animation be looped?
	*/
    void addAnimation(const char *name, const FlxInitializerList<unsigned int>& frames, float time = 0,
                      bool looped = true);

    /**
	*  Play specified animation
	*  @param animName Animation name
	*/
    void play(const char *animName);
	
	/**
	*  Stop current animation
	*/
    void stop();
	
    /**
	*  Draw event (to override)
	*/
    virtual void draw();
	
	/**
	*  Update event (to override)
	*  Anyway, keep in mind that this implementations should be called in inherited function
	*/
    virtual void update();
};

#endif

