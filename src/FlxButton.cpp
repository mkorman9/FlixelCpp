#include "FlxButton.h"
#include "FlxG.h"

FlxButton::FlxButton(float X, float Y, const char *buttonImage, int Width, int Height, int statesCount) {
    x = X;
    y = Y;
    width = Width;
    height = Height;
    buttonStates = statesCount;
    multitouch = true;
    mouseOver = false;
    down = false;
    pressed = false;
    released = false;

    // setup sprite
    sprite = new FlxSprite(x, y, buttonImage, width, height);
    sprite->collisions = false;
    sprite->scrool = false;

    sprite->addAnimation("default", FlxInitializerList<unsigned int>(0));
    if(statesCount > 1) sprite->addAnimation("down", FlxInitializerList<unsigned int>(1));
    if(statesCount > 2) sprite->addAnimation("mouseOn", FlxInitializerList<unsigned int>(2));

    sprite->isGUI = true;
    sprite->play("default");

    onText = offText = 0;
    add(sprite);
}


void FlxButton::update() {

    // update all members position
    sprite->x = x;
    sprite->y = y;

    if(onText) {
        onText->x = x + ((width - onText->width) / 2);
        onText->y = y + ((height - onText->height) / 2);

        offText->x = x + ((width - offText->width) / 2);
        offText->y = y + ((height - offText->height) / 2);
    }

    // update button state
	mouseOver = false;
    down = false;
    pressed = false;
    released = false;

    unsigned int mousesCount = FlxG::mousesList.size();
    if(mousesCount != 0 && active) {
        if(!multitouch) mousesCount = 1;

        for(unsigned int i = 0; i < mousesCount; i++) {
            FlxMouse *m = FlxG::mousesList[i];

            FlxRect buttonBounds(x, y, width, height);
            FlxRect mouseBounds(m->x, m->y, 1, 1);

            // is mouse over button?
            if(buttonBounds.overlaps(mouseBounds)) {
                if(!m->leftDown) {
                    mouseOver = true;
                }
                else {
                    down = true;
                    if(onDown != nullptr) onDown(this);
                }

                if(m->leftPressed) {
                    pressed = true;
                    if(onPressed != nullptr) onPressed(this);
                }
                else if(m->leftReleased) {
                    released = true;
                    if(onReleased != nullptr) onReleased(this);
                }
            }
        }
    }

    sprite->play("default");
    if(down && buttonStates > 1) sprite->play("down");
    else if(mouseOver && buttonStates > 2) sprite->play("mouseOn");

    if(onText) {
        if(down) {
            onText->visible = true;
            offText->visible = false;
        }
        else {
            onText->visible = false;
            offText->visible = true;
        }
    }

    FlxGroup::update();
}


void FlxButton::setTextFormat(const wchar_t *text, const char *font, int size, int color) {

    if(onText) {
        remove(onText);
        remove(offText);
    }

    onText = new FlxText(text, font, x, y, size, color);
    offText = new FlxText(text, font, x, y, size, color);

    add(onText);
    add(offText);
}


void FlxButton::draw() {
    FlxGroup::draw();
}
