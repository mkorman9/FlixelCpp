#include "FlxSound.h"
#include "backend/BackendHolder.h"

std::vector<FlxBackendSound*> FlxSound::Sounds;

FlxSound::FlxSound(const char *path) {
    soundBufferPtr = BackendHolder::get().getBackend()->loadSound(path);
    soundPtr = NULL;
}


void FlxSound::play(float vol) {
    if(soundPtr) stop();

    soundPtr = BackendHolder::get().getBackend()->playSound(soundBufferPtr, vol);
    Sounds.push_back(soundPtr);
}


void FlxSound::stop() {
    if(!soundPtr) return;

    soundPtr->stop();
    soundPtr = NULL;
}


void FlxSound::pause() {
    if(!soundPtr) return;

    soundPtr->pause();
}


bool FlxSound::isPlaying() {
    if(!soundPtr) return false;

    return soundPtr->isPlaying();
}


bool FlxSound::isPaused() {
    if(!soundPtr) return false;

    return soundPtr->isPlaying();
}


void FlxSound::setLooped(bool loop) {
    if(!soundPtr) return;

    soundPtr->setLoop(loop);
}
