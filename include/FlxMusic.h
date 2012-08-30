/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_MUSIC_H_
#define _FLX_MUSIC_H_

#include "backend/cpp.h"
#include "FlxBackendBase.h"

/*
*  Music class
*/
class FlxMusic {

private:
    FlxBackendMusic *musicPtr;
public:
    static std::vector<FlxBackendMusic*> Music;

    FlxMusic(const char *path);

    void play(float vol);

    void stop();

    void pause();

    bool isPlaying();

    bool isPaused();

    void setLooped(bool loop);
};

#endif

