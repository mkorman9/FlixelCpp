#include "FlxPreloader.h"
#include "backend/BackendHolder.h"
#include "FlxG.h"

FlxPreloader *FlxPreloader::CurrentInstance;


void FlxPreloader::update() {

    unsigned int assets = imagesToLoad.size() + fontsToLoad.size() + musicToLoad.size() +
        soundsToLoad.size();
    if(!assets || (assetsLoaded == assets)) { percent = 100; FlxG::exitMessage = true; return; }

    percent = ((float)assetsLoaded / (float)assets) * 100.f;

    // load images?
    if(state == FLX_IMAGES_LOADING) {

        if(currentIterator > int(imagesToLoad.size() - 1)) {
            currentIterator = 0;
            state = FLX_FONTS_LOADING;
        }
        else {
            BackendHolder::get().getBackend()->loadImage(imagesToLoad[currentIterator].c_str());
            currentIterator++;
            assetsLoaded++;
        }
    }

    // or maybe fonts?
    else if(state == FLX_FONTS_LOADING) {

        if(currentIterator > int(fontsToLoad.size() - 1)) {
            currentIterator = 0;
            state = FLX_MUSIC_LOADING;
        }
        else {
            BackendHolder::get().getBackend()->loadFont(fontsToLoad[currentIterator].first.c_str(),
                                                        fontsToLoad[currentIterator].second);
            currentIterator++;
            assetsLoaded++;
        }
    }

    // or maybe music?
    else if(state == FLX_MUSIC_LOADING) {

        if(currentIterator > int(musicToLoad.size() - 1)) {
            currentIterator = 0;
            state = FLX_SOUNDS_LOADING;
        }
        else {
            BackendHolder::get().getBackend()->loadMusic(musicToLoad[currentIterator].c_str());
            currentIterator++;
            assetsLoaded++;
        }
    }

    // or sounds?
    else if(state == FLX_SOUNDS_LOADING) {

        if(currentIterator > int(soundsToLoad.size() - 1)) {
            currentIterator = 0;
            FlxG::exitMessage = true;
        }
        else {
            BackendHolder::get().getBackend()->loadSound(soundsToLoad[currentIterator].c_str());
            currentIterator++;
            assetsLoaded++;
        }
    }

    FlxGroup::update();
}


void FlxPreloader::draw() {
    FlxGroup::draw();
}


// static
void FlxPreloader::onUpdate() {
    CurrentInstance->update();
}


void FlxPreloader::onDraw() {
    CurrentInstance->draw();
}

