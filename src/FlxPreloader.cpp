#include "FlxPreloader.h"
#include "FlxG.h"

FlxPreloader *FlxPreloader::CurrentInstance;


void FlxPreloader::update() {

    unsigned int assets = imagesToLoad.size() + fontsToLoad.size() + musicToLoad.size() +
        soundsToLoad.size();
    if(!assets || (assetsLoaded == assets)) { percent = 100.f; FlxG::exitMessage = true; return; }

    percent = ((float)assetsLoaded / (float)assets) * 100.f;

    // load images?
    if(state == FLX_IMAGES_LOADING) {

        if(currentIterator > int(imagesToLoad.size() - 1)) {
            currentIterator = 0;
            state = FLX_FONTS_LOADING;
        }
        else {
            if(!FlxG::backend->loadImage(imagesToLoad[currentIterator].c_str())) {
                onError(imagesToLoad[currentIterator]);
            }

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
            if(!FlxG::backend->loadFont(fontsToLoad[currentIterator].first.c_str(),
                                                    fontsToLoad[currentIterator].second))
            {
               onError(fontsToLoad[currentIterator].first);
            }

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
			// don't load music now. music files should be streamed,
			// not loaded on the begining. Check file's existance
			if(!FlxG::backend->internalFileExists(musicToLoad[currentIterator].c_str())) {
                onError(musicToLoad[currentIterator]);
			}

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
            if(!FlxG::backend->loadSound(soundsToLoad[currentIterator].c_str())) {
                onError(soundsToLoad[currentIterator]);
            }

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

