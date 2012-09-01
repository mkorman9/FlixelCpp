/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_SHADER_H_
#define _FLX_SHADER_H_

#include "FlxVector.h"
#include "FlxBackendBase.h"

/*
*  Base shader class
*/
class FlxShader {

public:
    FlxBackendShader *data;

    // load shader to memory. Vertex shader is always default (defined by backend)
    FlxShader(const char *fragmentShaderFile);

    // set properties
    void setParameter(const char *name, float x);
    void setParameter(const char *name, float x, float y);
    void setParameter(const char *name, const FlxVector& vec);
    void setParameter(const char *name, float x, float y, float z);
    void setParameter(const char *name, float x, float y, float z, float w);
    void setParameter(const char *name, int rgb);
    void setParameter(const char *name, int rgb, float alpha);

    // set texture (pass NULL as texFile to obtain framebuffer texture)
    void setTexture(const char *name, const char *texFile);
};


/*
*  Group of shaders (help class for FlxG)
*/
class FlxShadersList {

public:
    std::vector<FlxShader*> members;

    FlxShader* add(FlxShader *s) {
        if(!s) return NULL;

        members.push_back(s);
        return s;
    }

    bool remove(FlxShader *s) {
        if(!s) return false;

        for(unsigned int i = 0; i < members.size(); i++) {
            if(members[i] == s) {
                members.erase(members.begin() + i);
                return true;
            }
        }

        return false;
    }

    void clear() {
        members.clear();
    }
};


#endif




