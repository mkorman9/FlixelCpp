#include "FlxText.h"
#include "backend/BackendHolder.h"

FlxText::FlxText(const char *Text, const char *Font, float X, float Y, int Size, int Color) {
    x = X;
    y = Y;
    text = Text;
    font = NULL;

    collisions = false;
    scrool = false;

    setFormat(Font, Size, Color);
}


void FlxText::setFormat(const char *Font, int Size, int Color) {

    font = BackendHolder::get().getBackend()->loadFont(Font, Size);
    color = Color;
    size = Size;
}


void FlxText::update() {
    if(!active) return;

    FlxObject::update();
}


void FlxText::draw() {
    if(!visible) return;

    FlxVector sizeOfText = BackendHolder::get().getBackend()->drawText(text.c_str(), font, size, x, y,
                                                                       scale, angle, color, scrool, alpha);

    width = (int)sizeOfText.x;
    height = (int)sizeOfText.y;

    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = width;
    hitbox.height = height;
}

