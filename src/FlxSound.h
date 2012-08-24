/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_SOUND_H_
#define _FLX_SOUND_H_

#include "backend/cpp.h"
#include "FlxBackendBase.h"

/*
*  Sound class
*/
class FlxSound {

private:
    FlxBackendSound *soundPtr;
    void *soundBufferPtr;
public:
    static std::vector<FlxBackendSound*> Sounds;

    FlxSound(const char *path);

    void play(float vol);

    void stop();

    void pause();

    bool isPlaying();

    bool isPaused();

    void setLooped(bool loop);
};

#endif

