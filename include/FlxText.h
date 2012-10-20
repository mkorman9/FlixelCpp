/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_TEXT_H_
#define _FLX_TEXT_H_

#include "FlxObject.h"
#include "FlxBackendBase.h"

/**
*  Text rendering helper
*/
class FlxText : public FlxObject {

private:
    void *font;
    FlxBaseText *textData;
    bool needUpdate;
    int size, lastColor;
    std::wstring lastText;
	float lastAlpha;

    void updateBuffer();
public:

    /**
	*  Text to draw (Unicode format)
	*/
    std::wstring text;


    /**
	*  Default constructor
	*  @param text Text to render (Unicode format)
	*  @param font Path to font (must be in local device storage)
	*  @param x Position of text in X-axis
	*  @param y Position of twxt in Y-axis
	*  @param size Size of text
	*  @param Color Color of text (24-bit, no alpha)
	*/
    FlxText(const wchar_t *text, const char *font, float x = 0, float y = 0, int size = 32, int Color = 0x000000);

    /**
	*  Default destructor
	*/
    virtual ~FlxText();

    /**
	*  Set text design
	*  @param font Path to font (must be in local device storage)
	*  @param Size Size of text
	*  @param Color Color of text (24-bit, no alpha)
	*/
    void setFormat(const char *font, int Size, int Color);

	/**
	*  Update event (to override)
	*/
    virtual void update();
	
	/**
	*  Draw event (to override)
	*/
    virtual void draw();
};

#endif


