/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_BACKEND_BASE_H_
#define _FLX_BACKEND_BASE_H_

#include "FlxVector.h"
#include "FlxRect.h"
#include "FlxHttpRequest.h"

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
*  Template for shader
*/
class FlxBackendShader {

public:
    virtual ~FlxBackendShader() { }

    virtual void setParameter(const char *name, float x) = 0;
    virtual void setParameter(const char *name, float x, float y) = 0;
    virtual void setParameter(const char *name, float x, float y, float z) = 0;
    virtual void setParameter(const char *name, float x, float y, float z, float w) = 0;
    virtual void setParameter(const char *name, FlxBackendImage *img) = 0;
};

/*
*  Template for sound
*/
class FlxBackendSound {

public:
    virtual ~FlxBackendSound() { }

    virtual void play() = 0;
    virtual void stop() = 0;

    virtual void setLoop(bool t) = 0;
    virtual void setVolume(float vol) = 0;

    virtual bool isPlaying() = 0;
};

/*
*  Template for music
*/
class FlxBackendMusic {

public:
    virtual ~FlxBackendMusic() { }

    virtual void play() = 0;
    virtual void stop() = 0;

    virtual void setLoop(bool t) = 0;
    virtual void setVolume(float vol) = 0;

    virtual bool isPlaying() = 0;
};

// Text struct
struct FlxBaseText {
    std::string text;
    int color, size;
    float alpha, angle;
    FlxVector scale;
    FlxVector bounds;

    void *data, *font;
};


/*
*  Library backend base class.
*  Template class for loading assets, application/input managment and rendering
*/
class FlxBackendBase {

public:
    // app managment and input
    virtual bool setupSurface(const char *title, int width, int height) = 0;
    virtual void mainLoop(void (*onUpdate)(), void (*onDraw)()) = 0;
    virtual FlxVector getScreenSize() = 0;
    virtual void exitApplication() = 0;
    virtual bool* getKeysDown() = 0;
    virtual bool isKeyDown(int code) = 0;
    virtual FlxVector getMousePosition(int index) = 0;
    virtual bool getMouseButtonState(int button, int index) = 0;
    virtual void showMouse(bool show) = 0;

    // image rendering
    virtual void drawImage(FlxBackendImage *img, float x, float y, FlxVector scale, float angle,
                        FlxRect source, int color, bool flipped, bool scrool, float alpha) = 0;

    // text rendering
    virtual FlxBaseText *createText(const char *text, void *font, int size, FlxVector scale, float angle,
                                   int color, float alpha) = 0;
    virtual void destroyText(FlxBaseText *data) = 0;
    virtual void drawText(FlxBaseText *text, float x, float y, bool scrool) = 0;

    // special effects
    virtual bool isShadersSupported() = 0;
    virtual FlxBackendShader* loadShader(const char *path) = 0;
    virtual void drawShader(FlxBackendShader *shader) = 0;

    // image loading
    virtual FlxBackendImage* createImage(int width, int height, int color, float alpha) = 0;
    virtual FlxBackendImage *loadImage(const char *path) = 0;

    // text loading
    virtual void *loadFont(const char *path, int fontSize) = 0;

    // audio
    virtual void* loadSound(const char *path) = 0;
    virtual FlxBackendSound* playSound(void *sound, float vol) = 0;
    virtual FlxBackendMusic* loadMusic(const char *path) = 0;
    virtual void playMusic(FlxBackendMusic *music, float vol) = 0;

    // file I/O
    virtual void saveData(const char *path, const std::map<std::string, std::string>& data) = 0;
    virtual bool loadData(const char *path, std::map<std::string, std::string>& data) = 0;

    // network
    virtual bool sendHttpRequest(FlxHttpRequest *req, FlxHttpResponse& resp) = 0;
};

#endif

