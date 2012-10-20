/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_SOUND_H_
#define _FLX_SOUND_H_

#include "backend/cpp.h"
#include "FlxBackendBase.h"

/**
*  Sound object
*/
class FlxSound {

private:
    FlxBackendSound *soundPtr;
    void *soundBufferPtr;
public:

	/**
	*  All active sound objects (Internal! Do not touch!)
	*/
    static std::vector<FlxBackendSound*> Sounds;

	/**
	*  Default constructor
	*  @param path Path to sound file (Must be in local device storage)
	*/
    FlxSound(const char *path);

	/**
	*  Play sound
	*  @param vol Volume in range 0 - 1
	*/
    void play(float vol);

	/**
	*  Stop playing
	*/
    void stop();

	/**
	*  Is sound currently playing?
	*  @return <code>true</code> if it's playing, <code>false</code> if it's not
	*/
    bool isPlaying();

	/**
	*  Should sound be played infinitely? (<b>NOTE: This function is currently bugged</b>)
	*  @return loop Yes or no
	*/
    void setLooped(bool loop);
};

#endif

