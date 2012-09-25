/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_SPRITE_H_
#define _FLX_SPRITE_H_

#include "FlxObject.h"
#include "FlxBackendBase.h"
#include "FlxAnim.h"

/*
*  Class represents drawable and animated graphic
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

    // flip sprite horizontaly
    bool flipped;

    // is animation finished?
    bool animationFinished;


    // constructor
    FlxSprite(float x = 0, float y = 0, const char *gfx = NULL, int Width = 0, int Height = 0);

    // destructor
    virtual ~FlxSprite();

    // reset internal sprite data
    void reset();

    // load image to memory
    bool loadGraphic(const char *gfx, int Width = 0, int Height = 0);

    // create texture in memory
    void makeGraphic(int width, int height, int color);

    // Add animation
    void addAnimation(const char *name, const FlxInitializerList<unsigned int>& frames, float time = 0,
                      bool looped = true);

    // plays and stops animation
    void play(const char *animName);
    void stop();

    virtual void draw();
    virtual void update();
};

#endif



