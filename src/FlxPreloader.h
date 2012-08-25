/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_PRELOADER_H_
#define _FLX_PRELOADER_H_

#include "FlxGroup.h"
#include "backend/cpp.h"

// current preloader state
enum FlxLoadingState {
    FLX_IMAGES_LOADING,
    FLX_FONTS_LOADING,
    FLX_MUSIC_LOADING,
    FLX_SOUNDS_LOADING
};


/*
*  Loading screen class
*/
class FlxPreloader : public FlxGroup {

private:
    std::vector<std::string> imagesToLoad;
    std::vector<std::pair<std::string, int> > fontsToLoad;
    std::vector<std::string> musicToLoad;
    std::vector<std::string> soundsToLoad;
    float percent;
public:

    FlxLoadingState state;

    FlxPreloader() {
        state = FLX_IMAGES_LOADING;
    }

    ~FlxPreloader() {
        clear();
    }

    virtual void create() {
    }

    virtual void progress(float percent) {

    }

    virtual void update();
    virtual void draw();

    void loadImage(const std::string& path) {
        imagesToLoad.push_back(path);
    }

    void loadFont(const std::string& path, int size) {
        fontsToLoad.push_back(std::make_pair(path, size));
    }

    void loadMusic(const std::string& path) {
        musicToLoad.push_back(path);
    }

    void loadSound(const std::string& path) {
        soundsToLoad.push_back(path);
    }

    void run();
};

#endif


