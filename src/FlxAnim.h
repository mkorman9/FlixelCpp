/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_ANIM_H_
#define _FLX_ANIM_H_

#include "backend/cpp.h"

/*
*  Support animation structure
*/
struct FlxAnim {

    std::string name;
    float time;
    std::vector<unsigned int> frames;
    bool looped;

    FlxAnim(const std::string &Name, const std::vector<unsigned int> &Frames, float FrameRate = 0, bool Looped = true) {
        name = Name;
        frames = Frames;
        looped = Looped;
        time = FrameRate;
    };
};

#endif




