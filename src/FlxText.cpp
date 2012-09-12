#include "FlxText.h"
#include "backend/BackendHolder.h"

FlxText::FlxText(const wchar_t *Text, const char *Font, float X, float Y, int Size, int Color) {
    x = X;
    y = Y;
    text = lastText = Text;
    font = NULL;
    textData = NULL;
    lastColor = Color;
	lastAlpha = lastScaleX = lastScaleY = 1.f;
	lastAngle = 0.f;
    isGUI = true;

    collisions = false;
    scrool = false;

    setFormat(Font, Size, Color);
}


void FlxText::setFormat(const char *Font, int Size, int Color) {

    font = BackendHolder::get().getBackend()->loadFont(Font, Size);
    color = Color;
    size = Size;

    needUpdate = true;
}


void FlxText::setText(const wchar_t *Text) {
    text = Text;
}


void FlxText::update() {
    if(!active) return;

    if(color != lastColor || lastText != text || lastAlpha != alpha || lastScaleX != scale.x ||
		lastScaleY != scale.y || lastAngle != angle)
	{
        needUpdate = true;
    }

    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = width;
    hitbox.height = height;

    if(lastColor != color) lastColor = color;
    if(lastText != text) lastText = text;
	if(alpha != lastAlpha) lastAlpha = alpha;
	if(lastScaleX != scale.x) lastScaleX = scale.x;
	if(lastScaleY != scale.y) lastScaleY = scale.y;
	if(lastAngle != angle) lastAngle = angle;

    FlxObject::update();
}


void FlxText::draw() {
    if(!visible) return;

    if(needUpdate) {
        updateBuffer();
    }

    BackendHolder::get().getBackend()->drawText(textData, x, y, scrool, scroolFactor);
}


void FlxText::updateBuffer() {

    BackendHolder::get().getBackend()->destroyText(textData);
    textData = BackendHolder::get().getBackend()->createText(text.c_str(), font, size, scale, angle, color,
                                                        alpha);

    if(textData) {
        width = (int)textData->bounds.x;
        height = (int)textData->bounds.y;
    }

    needUpdate = false;
}
