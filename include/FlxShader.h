/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_SHADER_H_
#define _FLX_SHADER_H_

#include "FlxVector.h"
#include "FlxBackendBase.h"

/**
*  Base special FX class
*/
class FlxShader {

public:
	
	/**
	*  Internal shader data
	*/
    FlxBackendShader *data;

	/**
	*  Default constructor. Loads shader to memory. <b>NOTE: Vertex shader is always default</b>
	*  @param fragmentShaderFile Path to fragment shader file (in local device's storage). 
	*/
    FlxShader(const char *fragmentShaderFile);

	/**
	*  Set uniform's value.
	*  @param name Uniform name
	*  @param x Value #1
	*/
    void setParameter(const char *name, float x);
	
	/**
	*  Set uniform's value.
	*  @param name Uniform name
	*  @param x Value #1
	*  @param y Value #2
	*/
    void setParameter(const char *name, float x, float y);
	
	/**
	*  Set uniform's value.
	*  @param name Uniform name
	*  @param vec Vector of 2 floating point values to set
	*/
    void setParameter(const char *name, const FlxVector& vec);
	
	/**
	*  Set uniform's value.
	*  @param name Uniform name
	*  @param x Value #1
	*  @param y Value #2
	*  @param z Value #3
	*/
    void setParameter(const char *name, float x, float y, float z);
	
	/**
	*  Set uniform's value.
	*  @param name Uniform name
	*  @param x Value #1
	*  @param y Value #2
	*  @param z Value #3
	*  @param w Value #4
	*/
    void setParameter(const char *name, float x, float y, float z, float w);
	
	/**
	*  Set uniform's value (vec3)
	*  @param name Uniform name
	*  @param rgb Color to set
	*/
    void setParameter(const char *name, int rgb);
	
	/**
	*  Set uniform's value (vec4)
	*  @param name Uniform name
	*  @param rgb Color to set
	*  @param alpha Alpha to set
	*/
    void setParameter(const char *name, int rgb, float alpha);

	/**
	*  Bind sampler's value.
	*  @param name Sampler name
	*  @param texFile Path to texture file (in local storage) or <code>NULL</code>
	*  if you want to bind default framebuffer.
	*/
    void setTexture(const char *name, const char *texFile);
};


/**
*  Group of shaders (help class for FlxG)
*/
class FlxShadersList {

public:

	/**
	*  Collection of shaders
	*/
    std::vector<FlxShader*> members;
	
    /**
	*  Add new shader to group
	*  @param s Shader to add
	*  @return Pointer to <code>s</code>, for chaining
	*/
    FlxShader* add(FlxShader *s) {
        if(!s) return NULL;

        members.push_back(s);
        return s;
    }
	
    /**
	*  Remove shader from group
	*  @param s Shader to remove
	*  @return <code>true</code> if removement was successful. <code>false</code> if shader was not found in group
	*/
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
	
    /**
	*  Remove all shaders from group
	*/
    void clear() {
        for(unsigned int i = 0; i < members.size(); i++) {
            if(members[i]) delete members[i];
        }

        members.clear();
    }
};


#endif

