#include "FlxSprite.h"
#include "backend/BackendHolder.h"

FlxSprite::FlxSprite(float X, float Y, const char *gfx, int Width, int Height) {
    x = X;
    y = Y;
    sourceX = sourceY = 0;
    flipped = false;
    currentFrame = currentFrameNumber = 0;
    frameCounter = 0;
    currentAnimation = NULL;

    if(gfx) loadGraphic(gfx, Width, Height);
}


FlxSprite::~FlxSprite() {
    for(unsigned int i = 0; i < animations.size(); i++) {
        delete animations[i];
    }
}


bool FlxSprite::loadGraphic(const char *gfx, int Width, int Height) {

    graphic = BackendHolder::get().getBackend()->loadImage(gfx);
    width = (Width == 0 ? graphic->getWidth() : Width);
    height = (Height == 0 ? graphic->getHeight() : Height);

    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = width;
    hitbox.height = height;

    return true;
}

void FlxSprite::makeGraphic(int Width, int Height, int color) {
    graphic = BackendHolder::get().getBackend()->createImage(Width, Height, color);
    width = hitbox.width = Width;
    height = hitbox.height = Height;
}


void FlxSprite::update() {
    if(!active) return;

    updateAnimation();
    FlxObject::update();
}


void FlxSprite::draw() {
    if(!graphic || !visible) return;

    BackendHolder::get().getBackend()->drawImage(graphic, x, y, scale, angle,
                                                 FlxRect(sourceX, sourceY, width, height), color, flipped, scrool);
}


void FlxSprite::addAnimation(const char *name, const std::vector<unsigned int>& frames, float time, bool looped) {
    animations.push_back(new FlxAnim(name, frames, time, looped));
}


void FlxSprite::play(const char *animName) {
    for(unsigned int i = 0; i < animations.size(); i++) {
        if(animations[i]->name == animName) {
            currentAnimation = animations[i];

            if(currentAnimation->frames.size() != 0) {
                currentFrame = currentAnimation->frames[0];
                calcFrame();
            }
        }
    }
}


void FlxSprite::stop() {
    currentAnimation = NULL;
    frameCounter = 0;
}


void FlxSprite::updateAnimation() {
    if(currentAnimation != NULL) {

        frameCounter += BackendHolder::get().getBackend()->getDeltaTime();
        if(frameCounter >= currentAnimation->time) {

            frameCounter = 0;
            currentFrameNumber++;

            // finish animation?
            if(currentFrameNumber >= (int)currentAnimation->frames.size()) {
                currentFrameNumber = 0;
                currentFrame = currentAnimation->frames[0];

                if(!currentAnimation->looped) { stop(); calcFrame(); return; }
            }
            else {
                currentFrame = currentAnimation->frames[currentFrameNumber];
            }
        }

        calcFrame();
    }
    else {
        sourceX = 0;
        sourceY = 0;
    }
}

void FlxSprite::calcFrame() {

    unsigned int rx = currentFrame * width;
    unsigned int ry = 0;

    unsigned int w = graphic->getWidth();
    if(rx >= w) {
        ry = (rx / w) * width;
        rx = rx % w;
    }

    sourceX = rx;
    sourceY = ry;
}
