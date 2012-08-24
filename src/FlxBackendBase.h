/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_BACKEND_BASE_H_
#define _FLX_BACKEND_BASE_H_

#include "FlxVector.h"
#include "FlxRect.h"

#define FLX_BUTTON_LEFT 0
#define FLX_BUTTON_MIDDLE 1
#define FLX_BUTTON_RIGHT 2

/*
*  Template for image.
*/
class FlxBackendImage {

public:
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual int getFormat() = 0;
};

/*
*  Template for sound
*/
class FlxBackendSound {

public:
    virtual ~FlxBackendSound() { }

    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;

    virtual void setLoop(bool t) = 0;
    virtual void setVolume(float vol) = 0;

    virtual bool isPlaying() = 0;
    virtual bool isPaused() = 0;
};

/*
*  Template for music
*/
class FlxBackendMusic {

public:
    virtual ~FlxBackendMusic() { }

    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;

    virtual void setLoop(bool t) = 0;
    virtual void setVolume(float vol) = 0;

    virtual bool isPlaying() = 0;
    virtual bool isPaused() = 0;
};


/*
*  Library backend base class.
*  Template class for loading assets, application/input managment and rendering
*/
class FlxBackendBase {

public:
    virtual bool setupSurface(const char *title, int width, int height) = 0;
    virtual FlxVector getScreenSize() = 0;
    virtual bool exitMessage() = 0;
    virtual void exitApplication() = 0;
    virtual FlxVector getMousePosition(int index) = 0;
    virtual bool getMouseButtonState(int button, int index) = 0;
    virtual int getMousePointers() = 0;
    virtual bool* getKeysDown() = 0;
    virtual bool isKeyDown(int code) = 0;
    virtual float getDeltaTime() = 0;
    virtual void updateInput() = 0;
    virtual void showMouse(bool show) = 0;

    virtual void beginScene(int color) = 0;
    virtual void drawImage(FlxBackendImage *img, float x, float y, FlxVector scale, float angle,
                        FlxRect source, int color, bool flipped, bool scrool) = 0;
    virtual void* createText(const char *text, void *font, int size) = 0;
    virtual void destroyText(void *text) = 0;
    virtual void drawText(void *text, float x, float y, FlxVector scale, float angle, int color, bool scrool) = 0;
    virtual void endScene() = 0;

    virtual FlxBackendImage* createImage(int width, int height, int color) = 0;
    virtual FlxBackendImage *loadImage(const char *path) = 0;
    virtual void *loadFont(const char *path, int fontSize) = 0;

    virtual FlxVector getTextSize(void *text) = 0;

    virtual void* loadSound(const char *path) = 0;
    virtual FlxBackendMusic* loadMusic(const char *path) = 0;
    virtual FlxBackendSound* playSound(void *sound, float vol) = 0;
    virtual void playMusic(FlxBackendMusic *music, float vol) = 0;
};

#endif

