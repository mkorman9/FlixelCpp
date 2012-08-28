/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_TEXT_H_
#define _FLX_TEXT_H_

#include "FlxObject.h"
#include "FlxBackendBase.h"

/*
*  Text entity
*/
class FlxText : public FlxObject {

private:
    void *font;
    FlxBaseText *textData;
    bool needUpdate;
    int size, lastColor;
    std::string lastText;

    void updateBuffer();
public:

    // text
    std::string text;


    // Default constructor
    FlxText(const char *text, const char *font, float x = 0, float y = 0, int size = 32, int Color = 0x000000);

    // Set text's design
    void setFormat(const char *font, int Size, int Color);

    // Set text
    void setText(const char *text);

    virtual void update();
    virtual void draw();
};

#endif


