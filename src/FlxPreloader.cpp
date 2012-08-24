#include "FlxPreloader.h"
#include "backend/BackendHolder.h"
#include "FlxG.h"

void FlxPreloader::run() {

    unsigned int assets = imagesToLoad.size() + fontsToLoad.size() + musicToLoad.size() +
        soundsToLoad.size();
    unsigned int assetsLoaded = 0;

    while(assets != assetsLoaded) {
        BackendHolder::get().getBackend()->updateInput();
        FlxG::elapsed = BackendHolder::get().getBackend()->getDeltaTime();
        FlxG::mouse->updateState();

        // load data chunk here
        if(state == FLX_IMAGES_LOADING) {
            for(unsigned int i = 0; i < imagesToLoad.size(); i++) {
                BackendHolder::get().getBackend()->loadImage(imagesToLoad[i].c_str());
                assetsLoaded++;

                update((assetsLoaded / assets) * 100.f);
            }

            state = FLX_FONTS_LOADING;
        }
        else if(state == FLX_FONTS_LOADING) {
            for(unsigned int i = 0; i < fontsToLoad.size(); i++) {
                BackendHolder::get().getBackend()->loadFont(fontsToLoad[i].first.c_str(), fontsToLoad[i].second);
                assetsLoaded++;

                update((assetsLoaded / assets) * 100.f);
            }

            state = FLX_MUSIC_LOADING;
        }
        else if(state == FLX_MUSIC_LOADING) {
            for(unsigned int i = 0; i < musicToLoad.size(); i++) {
                BackendHolder::get().getBackend()->loadMusic(musicToLoad[i].c_str());
                assetsLoaded++;

                update((assetsLoaded / assets) * 100.f);
            }

            state = FLX_SOUNDS_LOADING;
        }
        else if(state == FLX_SOUNDS_LOADING) {
            for(unsigned int i = 0; i < soundsToLoad.size(); i++) {
                BackendHolder::get().getBackend()->loadSound(soundsToLoad[i].c_str());
                assetsLoaded++;

                update((assetsLoaded / assets) * 100.f);
            }
        }

        BackendHolder::get().getBackend()->beginScene(0xff000000);
        draw();
        BackendHolder::get().getBackend()->endScene();

        FlxG::key->updateState();
    }
}
