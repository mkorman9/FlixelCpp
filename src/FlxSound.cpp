#include "FlxSound.h"
#include "FlxG.h"

std::vector<FlxBackendSound*> FlxSound::Sounds;

FlxSound::FlxSound(const char *path) {
    soundBufferPtr = FlxG::backend->loadSound(path);
    soundPtr = NULL;
}


void FlxSound::play(float vol) {
    if(soundPtr) stop();

    soundPtr = FlxG::backend->playSound(soundBufferPtr, vol);
    Sounds.push_back(soundPtr);
}


void FlxSound::stop() {
    if(!soundPtr) return;

    soundPtr->stop();
    soundPtr = NULL;
}


bool FlxSound::isPlaying() {
    if(!soundPtr) return false;

    return soundPtr->isPlaying();
}


void FlxSound::setLooped(bool loop) {
    if(!soundPtr) return;

    soundPtr->setLoop(loop);
}
