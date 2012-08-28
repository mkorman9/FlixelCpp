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
    std::map<std::string, FlxBackendImage*> images;
    std::map<std::string, void*> fonts;
    std::map<std::string, FlxBackendMusic*> music;
    std::map<std::string, void*> sounds;
    sf::Clock clock;

    void (*touchBegin)(int id, float, float);
    void (*touchEnd)(int id, float, float);

    void updateEvents();
public:
    virtual bool setupSurface(const char *title, int width, int height);
    virtual void mainLoop(void (*onUpdate)(), void (*onDraw)());
    virtual void setCallbacks(void (*onTouchBegin)(int id, float, float),
                              void (*onTouchEnd)(int id, float, float));
    virtual FlxVector getScreenSize();
    virtual void exitApplication();
    virtual bool* getKeysDown();
    virtual bool isKeyDown(int code);
    virtual FlxVector getMousePosition(int index);
    virtual bool getMouseButtonState(int button, int index);
    virtual void showMouse(bool show);

    virtual void drawImage(FlxBackendImage *img, float x, float y,  FlxVector scale, float angle,
                           FlxRect source, int color, bool flipped, bool scrool, float alpha);
    virtual FlxVector drawText(const char *text, void *font, int size, float x, float y, FlxVector scale, float angle, int color,
                          bool scrool, float alpha);

    virtual FlxBackendImage* createImage(int width, int height, int color, float alpha);
    virtual FlxBackendImage *loadImage(const char *path);

    virtual void *loadFont(const char *path, int fontSize);

    virtual void* loadSound(const char *path);
    virtual FlxBackendMusic* loadMusic(const char *path);
    virtual FlxBackendSound* playSound(void *sound, float vol);
    virtual void playMusic(FlxBackendMusic *music, float vol);

    virtual void saveData(const char *path, const std::map<std::string, std::string>& data);
    virtual bool loadData(const char *path, std::map<std::string, std::string>& data);
};

#endif
