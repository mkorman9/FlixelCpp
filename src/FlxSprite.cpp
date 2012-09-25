#include "FlxSprite.h"
#include "FlxG.h"

FlxSprite::FlxSprite(float X, float Y, const char *gfx, int Width, int Height) {
    x = X;
    y = Y;

    reset();

    if(gfx) loadGraphic(gfx, Width, Height);
}


void FlxSprite::reset() {
    sourceX = sourceY = 0;
    flipped = animationFinished = false;
    currentFrame = currentFrameNumber = 0;
    frameCounter = 0;
    currentAnimation = NULL;
}


FlxSprite::~FlxSprite() {
    for(unsigned int i = 0; i < animations.size(); i++) {
        delete animations[i];
    }
}


bool FlxSprite::loadGraphic(const char *gfx, int Width, int Height) {

    graphic = FlxG::backend->loadImage(gfx);
    width = (Width == 0 ? graphic->getWidth() : Width);
    height = (Height == 0 ? graphic->getHeight() : Height);

    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = width;
    hitbox.height = height;

    return true;
}


void FlxSprite::makeGraphic(int Width, int Height, int color) {
    graphic = FlxG::backend->createImage(Width, Height, color, alpha);
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

    FlxVector move = FlxG::scroolVector;
    move.x *= scroolFactor.x;
    move.y *= scroolFactor.y;
    if(!scrool) { move.x = move.y = 0; }

    FlxG::backend->drawImage(graphic, x + move.x, y + move.y, scale, angle,
                            FlxRect(sourceX, sourceY, width, height), color,
                            flipped, alpha);
}


void FlxSprite::addAnimation(const char *name, const FlxInitializerList<unsigned int>& frames,
                             float time, bool looped)
{
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

    if(animationFinished) animationFinished = false;

    if(currentAnimation != NULL) {

        //frameCounter += BackendHolder::get().getBackend()->getDeltaTime();
        frameCounter += FlxG::fixedTime;

        if(frameCounter >= currentAnimation->time) {

            frameCounter = 0;
            currentFrameNumber++;

            // finish animation?
            if(currentFrameNumber >= (int)currentAnimation->frames.size()) {
                currentFrameNumber = 0;
                currentFrame = currentAnimation->frames[0];

                if(!currentAnimation->looped) {
                    stop();
                    animationFinished = true;
                    return;
                }
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
        ry = (rx / w) * height;
        rx %= w;
    }

    sourceX = rx;
    sourceY = ry;
}
