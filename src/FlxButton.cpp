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
    sprite->collidate = false;
    sprite->scrool = false;

    std::vector<unsigned int> buttonOffFrame;
    buttonOffFrame.push_back(0);

    std::vector<unsigned int> buttonOnFrame;
    buttonOnFrame.push_back(1);

    std::vector<unsigned int> buttonMouseOnFrame;
    buttonMouseOnFrame.push_back(2);

    sprite->addAnimation("default", buttonOffFrame);
    if(statesCount > 1) sprite->addAnimation("down", buttonOnFrame);
    if(statesCount > 2) sprite->addAnimation("mouseOn", buttonMouseOnFrame);

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
    unsigned int mousesCount = FlxG::mouse.size();
    if(mousesCount != 0) {
        if(!multitouch) mousesCount = 1;

        mouseOver = false;
        down = false;
        pressed = false;
        released = false;

        for(unsigned int i = 0; i < mousesCount; i++) {
            FlxMouse *m = FlxG::mouse[i];

            FlxRect buttonBounds(x, y, width, height);
            FlxRect mouseBounds(m->x, m->y, 1, 1);

            // is mouse over button?
            if(buttonBounds.overlaps(mouseBounds)) {
                if(!m->leftDown) mouseOver = true;
                else down = true;

                if(m->leftPressed) pressed = true;
                else if(m->leftReleased) released = true;
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


void FlxButton::setTextFormat(const char *text, const char *font, int size, int color) {

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
