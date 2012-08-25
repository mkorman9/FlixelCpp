#include "FlxPreloader.h"
#include "backend/BackendHolder.h"
#include "FlxG.h"

void FlxPreloader::run() {

    unsigned int assets = imagesToLoad.size() + fontsToLoad.size() + musicToLoad.size() +
        soundsToLoad.size();
    unsigned int assetsLoaded = 0;

    percent = 0;

    while(assets != assetsLoaded) {

        update();
        draw();

        // load data chunk here
        if(state == FLX_IMAGES_LOADING) {
            for(unsigned int i = 0; i < imagesToLoad.size(); i++) {
                BackendHolder::get().getBackend()->loadImage(imagesToLoad[i].c_str());
                assetsLoaded++;

                percent = ((float)assetsLoaded / (float)assets) * 100.f;
                update();
                draw();
            }

            state = FLX_FONTS_LOADING;
        }

        if(state == FLX_FONTS_LOADING) {
            for(unsigned int i = 0; i < fontsToLoad.size(); i++) {
                BackendHolder::get().getBackend()->loadFont(fontsToLoad[i].first.c_str(), fontsToLoad[i].second);
                assetsLoaded++;

                percent = ((float)assetsLoaded / (float)assets) * 100.f;
                update();
                draw();
            }

            state = FLX_MUSIC_LOADING;
        }

        if(state == FLX_MUSIC_LOADING) {
            for(unsigned int i = 0; i < musicToLoad.size(); i++) {
                BackendHolder::get().getBackend()->loadMusic(musicToLoad[i].c_str());
                assetsLoaded++;

                percent = ((float)assetsLoaded / (float)assets) * 100.f;
                update();
                draw();
            }

            state = FLX_SOUNDS_LOADING;
        }

        if(state == FLX_SOUNDS_LOADING) {
            for(unsigned int i = 0; i < soundsToLoad.size(); i++) {
                BackendHolder::get().getBackend()->loadSound(soundsToLoad[i].c_str());
                assetsLoaded++;

                percent = ((float)assetsLoaded / (float)assets) * 100.f;
                update();
                draw();
            }
        }
    }
}

void FlxPreloader::draw() {

    BackendHolder::get().getBackend()->beginScene(FlxG::bgColor);
    FlxGroup::draw();
    BackendHolder::get().getBackend()->endScene();
}

void FlxPreloader::update() {
    BackendHolder::get().getBackend()->updateInput();
    FlxG::elapsed = BackendHolder::get().getBackend()->getDeltaTime();

    progress(percent);
    FlxGroup::update();

    FlxG::updateMouses();
    FlxG::key->updateState();
}
