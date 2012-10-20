/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_MUSIC_H_
#define _FLX_MUSIC_H_

#include "backend/cpp.h"
#include "FlxBackendBase.h"

/**
*  Music object
*/
class FlxMusic {

private:
    FlxBackendMusic *musicPtr;
public:

	/**
	*  All active music objects (Internal! Do not touch!)
	*/
    static std::vector<FlxBackendMusic*> Music;
	
	
	/**
	*  Default constructor
	*  @param path Path to music file (Must be in local device storage)
	*/
    FlxMusic(const char *path);
	
	/**
	*  Play music
	*  @param vol Volume in range 0 - 1
	*/
    void play(float vol);
	
	/**
	*  Stop playing
	*/
    void stop();

	/**
	*  Is music currently playing?
	*  @return <code>true</code> if it's playing, <code>false</code> if it's not
	*/
    bool isPlaying();
	
	/**
	*  Should music be played infinitely? (<b>NOTE: This function is currently bugged</b>)
	*  @return loop Yes or no
	*/
    void setLooped(bool loop);
};

#endif

