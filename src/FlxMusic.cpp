#include "FlxMusic.h"
#include "backend/BackendHolder.h"

std::vector<FlxBackendMusic*> FlxMusic::Music;

FlxMusic::FlxMusic(const char *path) {
    musicPtr = BackendHolder::get().getBackend()->loadMusic(path);
}


void FlxMusic::play(float vol) {

    if(musicPtr) {
        BackendHolder::get().getBackend()->playMusic(musicPtr, vol);
        Music.push_back(musicPtr);
    }
}


void FlxMusic::stop() {
    if(!musicPtr) return;

    musicPtr->stop();
    musicPtr = NULL;
}


void FlxMusic::pause() {
    if(!musicPtr) return;

    musicPtr->pause();
}


bool FlxMusic::isPlaying() {
    if(!musicPtr) return false;

    return musicPtr->isPlaying();
}


bool FlxMusic::isPaused() {
    if(!musicPtr) return false;

    return musicPtr->isPlaying();
}


void FlxMusic::setLooped(bool loop) {
    if(!musicPtr) return;

    musicPtr->setLoop(loop);
}

