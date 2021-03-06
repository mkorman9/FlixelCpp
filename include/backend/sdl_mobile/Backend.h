/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_BACKEND_SDL_H_
#define _FLX_BACKEND_SDL_H_

#include "../../FlxBackendBase.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_net.h>

/*
*  SDL opengles2 renderer
*/
class SDL_Mobile_Backend : public FlxBackendBase {

private:
	SDL_Window* window;
    SDL_Renderer* renderer;
	
    bool keysDown[1024];
	bool exitMsg;
    std::map<std::string, FlxBackendImage*> images;
    std::map<std::string, void*> fonts;
    std::map<std::string, void*> sounds;
	std::vector<FlxBackendShader*> shaders;
	
	unsigned int framebuffer;
	int screenWidth;
	int screenHeight;
	
    void updateEvents();
public:
	virtual std::string getName() { return "SDL2/mobile"; }
	
    virtual bool setupSurface(const char *title, int width, int height, const char *icon);
    virtual void mainLoop(void (*onUpdate)(), void (*onDraw)());
    virtual FlxVector getScreenSize();
    virtual void exitApplication();
    virtual bool* getKeysDown();
    virtual bool isKeyDown(int code);
    virtual FlxVector getMousePosition(int index);
    virtual bool getMouseButtonState(int button, int index);
    virtual void showMouse(bool show);

    virtual void drawImage(FlxBackendImage *img, float x, float y, const FlxVector& scale, float angle,
                           const FlxRect& source, int color, bool flipped, float alpha);

    virtual FlxBaseText *createText(const wchar_t *text, void *font, int size, int color, float alpha);
    virtual void destroyText(FlxBaseText *data);
    virtual void drawText(FlxBaseText *text, float x, float y, const FlxVector& scale, float angle);

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

    virtual FlxBackendFile* openFile(const char *path, const char *mode, bool internal);
	
	virtual bool sendHttpRequest(FlxHttpRequest *req, FlxHttpResponse& resp);
};

#endif
