#include "FlxMouseHolder.h"
#include "FlxG.h"

int FlxMouseHolder::touchesCount() {
    return (int)FlxG::mousesList.size();
}


FlxMouse* FlxMouseHolder::first() {
    return FlxG::mousesList[0];
}


FlxMouse* FlxMouseHolder::down(int index) {

    if(index != -1) {
        if(FlxG::mousesList[index]->leftDown) return FlxG::mousesList[index];
    }
    else {
        for(unsigned int i = 0; i < FlxG::mousesList.size(); i++) {
            if(FlxG::mousesList[i]->leftDown) return FlxG::mousesList[i];
        }
    }

    return NULL;
}


FlxMouse* FlxMouseHolder::pressed(int index) {

    if(index != -1) {
        if(FlxG::mousesList[index]->leftPressed) return FlxG::mousesList[index];
    }
    else {
        for(unsigned int i = 0; i < FlxG::mousesList.size(); i++) {
            if(FlxG::mousesList[i]->leftPressed) return FlxG::mousesList[i];
        }
    }

    return NULL;
}


FlxMouse* FlxMouseHolder::released(int index) {

    if(index != -1) {
        if(FlxG::mousesList[index]->leftReleased) return FlxG::mousesList[index];
    }
    else {
        for(unsigned int i = 0; i < FlxG::mousesList.size(); i++) {
            if(FlxG::mousesList[i]->leftReleased) return FlxG::mousesList[i];
        }
    }

    return NULL;
}


FlxMouse* FlxMouseHolder::downOnArea(const FlxRect& area, int index) {
    FlxMouse *m = down(index);
    if(!m) return NULL;

    if(area.overlaps(FlxRect(m->x, m->y, 1, 1))) return m;
    return NULL;
}


FlxMouse* FlxMouseHolder::pressedOnArea(const FlxRect& area, int index) {
    FlxMouse *m = pressed(index);
    if(!m) return NULL;

    if(area.overlaps(FlxRect(m->x, m->y, 1, 1))) return m;
    return NULL;
}


FlxMouse* FlxMouseHolder::releasedOnArea(const FlxRect& area, int index) {
    FlxMouse *m = released(index);
    if(!m) return NULL;

    if(area.overlaps(FlxRect(m->x, m->y, 1, 1))) return m;
    return NULL;
}


bool FlxMouseHolder::middleDown() {
    return FlxG::mousesList[0]->middleDown;
}


bool FlxMouseHolder::middlePressed() {
    return FlxG::mousesList[0]->middlePressed;
}


bool FlxMouseHolder::middleReleased() {
    return FlxG::mousesList[0]->middleReleased;
}

bool FlxMouseHolder::rightDown() {
    return FlxG::mousesList[0]->rightDown;
}

bool FlxMouseHolder::rightPressed() {
    return FlxG::mousesList[0]->rightPressed;
}

bool FlxMouseHolder::rightReleased() {
    return FlxG::mousesList[0]->rightReleased;
}
