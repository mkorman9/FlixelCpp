#include "FlxMusic.h"
#include "FlxG.h"

std::vector<FlxBackendMusic*> FlxMusic::Music;

FlxMusic::FlxMusic(const char *path) {
    musicPtr = FlxG::backend->loadMusic(path);
}


void FlxMusic::play(float vol) {

    if(musicPtr) {
        FlxG::backend->playMusic(musicPtr, vol);
        Music.push_back(musicPtr);
    }
}


void FlxMusic::stop() {
    if(!musicPtr) return;

    musicPtr->stop();
    musicPtr = NULL;
}


bool FlxMusic::isPlaying() {
    if(!musicPtr) return false;

    return musicPtr->isPlaying();
}


void FlxMusic::setLooped(bool loop) {
    if(!musicPtr) return;

    musicPtr->setLoop(loop);
}

