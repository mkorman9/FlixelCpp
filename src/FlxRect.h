/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_RECT_H_
#define _FLX_RECT_H_

/*
*  Rectangle class
*/
class FlxRect {

public:
    float x;
    float y;
    int width;
    int height;

    FlxRect(float X = 0, float Y = 0, int Width = 0, int Height = 0) {
        x = X;
        y = Y;
        width = Width;
        height = Height;
    }

    bool overlaps(const FlxRect& second) {
        return !((x >= (second.x + second.width)) || (second.x >= (x + width)) || (y >= (second.y + second.height))
            || (second.y >= (y + height)));
    }
};

#endif



