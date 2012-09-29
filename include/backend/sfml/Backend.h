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
#include <SFML/Network.hpp>

/*
*  SFML renderer
*/
class SFML_Backend : public FlxBackendBase {

private:
    sf::RenderWindow *window;
    bool keysDown[1024];
    std::map<std::string, FlxBackendImage*> images;
    std::map<std::string, void*> fonts;
    std::map<std::string, FlxBackendMusic*> music;
    std::map<std::string, void*> sounds;
    std::vector<FlxBackendShader*> shaders;
    sf::Clock clock;
    bool fullscreen;

    GLuint framebuffer;

    void updateEvents();
public:
    SFML_Backend(bool fullscreen = false);
    virtual std::string getName() { return "SFML"; }

    virtual bool setupSurface(const char *title, int width, int height, const char *icon);
    virtual void mainLoop(void (*onUpdate)(), void (*onDraw)());
    virtual FlxVector getScreenSize();
    virtual void exitApplication();
    virtual bool* getKeysDown();
    virtual bool isKeyDown(int code);
    virtual FlxVector getMousePosition(int index);
    virtual bool getMouseButtonState(int button, int index);
    virtual void showMouse(bool show);

    virtual void drawImage(FlxBackendImage *img, float x, float y,  const FlxVector& scale, float angle,
                           const FlxRect& source, int color, bool flipped, float alpha);

    virtual FlxBaseText *createText(const wchar_t *text, void *font, int size, int color, float alpha);
    virtual void destroyText(FlxBaseText *data);
    virtual void drawText(FlxBaseText *text, float x, float y, const FlxVector& scale,
                                    float angle);

    virtual FlxBackendImage* createImage(int width, int height, int color, float alpha);
    virtual FlxBackendImage *loadImage(const char *path);

    virtual bool isShadersSupported();
    virtual FlxBackendShader* loadShader(const char *path);
    virtual void drawShader(FlxBackendShader *shader);

    virtual void *loadFont(const char *path, int fontSize);

    virtual void* loadSound(const char *path);
    virtual FlxBackendMusic* loadMusic(const char *path);
    virtual FlxBackendSound* playSound(void *sound, float vol);
    virtual void playMusic(FlxBackendMusic *music, float vol);

    virtual void saveData(const char *path, const std::map<std::string, std::string>& data);
    virtual bool loadData(const char *path, std::map<std::string, std::string>& data);
    virtual bool internalFileExists(const char *path);

    virtual bool sendHttpRequest(FlxHttpRequest *req, FlxHttpResponse& resp);
};

#endif
