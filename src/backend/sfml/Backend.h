/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_BACKEND_SFML_H_
#define _FLX_BACKEND_SFML_H_

#include "../../FlxBackendBase.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
*  SFML software renderer
*/
class SFML_Backend : public FlxBackendBase {

private:
    sf::RenderWindow *window;
    bool keysDown[1024];
    bool exitMsg;
    std::map<std::string, FlxBackendImage*> images;
    std::map<std::string, void*> fonts;
    std::map<std::string, FlxBackendMusic*> music;
    std::map<std::string, void*> sounds;
public:
    virtual bool setupSurface(const char *title, int width, int height);
    virtual FlxVector getScreenSize();
    virtual bool exitMessage();
    virtual void exitApplication();
    virtual FlxVector getMousePosition(int index);
    virtual bool getMouseButtonState(int button, int index);
    virtual int getMousePointers();
    virtual bool* getKeysDown();
    virtual bool isKeyDown(int code);
    virtual float getDeltaTime();
    virtual void updateInput();
    virtual void showMouse(bool show);

    virtual void beginScene(int color);
    virtual void drawImage(FlxBackendImage *img, float x, float y,  FlxVector scale, float angle,
                           FlxRect source, int color, bool flipped, bool scrool);
    virtual void* createText(const char *text, void *font, int size);
    virtual void destroyText(void *text);
    virtual void drawText(void *text, float x, float y, FlxVector scale, float angle, int color, bool scrool);
    virtual void endScene();

    virtual FlxBackendImage* createImage(int width, int height, int color);
    virtual FlxBackendImage *loadImage(const char *path);
    virtual void *loadFont(const char *path, int fontSize);

    virtual FlxVector getTextSize(void *text);

    virtual void* loadSound(const char *path);
    virtual FlxBackendMusic* loadMusic(const char *path);
    virtual FlxBackendSound* playSound(void *sound, float vol);
    virtual void playMusic(FlxBackendMusic *music, float vol);
};

#endif
