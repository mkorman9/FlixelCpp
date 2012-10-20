/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_ANIM_H_
#define _FLX_ANIM_H_

#include "backend/cpp.h"
#include "backend/FlxInitializerList.h"

/**
*  Support animation structure.
*/
struct FlxAnim {

    /**
    *  Name of the animation state
    */
    std::string name;

    /**
    *  Duration of full cycle (in seconds)
    */
    float time;

    /**
    *  Array of frame indices
    */
    std::vector<unsigned int> frames;

    /**
    *  Should animation end after full cycle?
    */
    bool looped;

    /**
    *  Default constructor
    *  @param Name Animation name
    *  @param Frames List of frame indices
    *  @param FrameRate Duration of full cycle (in seconds)
    *  @param Looped Should animation end after full cycle?
    */
    FlxAnim(const std::string &Name, const FlxInitializerList<unsigned int> &Frames,
            float FrameRate = 0, bool Looped = true)
    {
        name = Name;
        looped = Looped;
        time = FrameRate;

		for(auto it = Frames.arguments.begin(); it != Frames.arguments.end(); it++) {
			frames.push_back(*it);
		}
    };
};

#endif




