#include "FlxText.h"
#include "backend/BackendHolder.h"

FlxText::FlxText(const char *Text, const char *Font, float X, float Y, int Size, int color) {
    x = X;
    y = Y;
    text = Text;
    textPtr = NULL;
    font = NULL;

    collidate = false;

    setFormat(Font, Size, color);
}


void FlxText::setFormat(const char *Font, int Size, int Color) {

    font = BackendHolder::get().getBackend()->loadFont(Font, Size);
    color = Color;
    size = Size;

    updateFrame();
}


void FlxText::setText(const char *Text) {
    text = Text;
    updateFrame();
}


void FlxText::updateFrame() {
    if(!visible) return;

    BackendHolder::get().getBackend()->destroyText(textPtr);
    textPtr = BackendHolder::get().getBackend()->createText(text.c_str(), font, size);

    FlxVector size = BackendHolder::get().getBackend()->getTextSize(textPtr);
    width = (int)size.x;
    height = (int)size.y;

    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = width;
    hitbox.height = height;
}


void FlxText::update() {
    if(!active) return;

    FlxObject::update();
}


void FlxText::draw() {
    BackendHolder::get().getBackend()->drawText(textPtr, x, y, scale, angle, color);
}

