#include "FlxMouse.h"
#include "backend/BackendHolder.h"

FlxMouse::FlxMouse(int id) {
    lastLeftDown = lastRightDown = lastMiddleDown = false;
    leftDown = middleDown = rightDown = false;
    leftPressed = middlePressed = rightPressed = false;
    leftReleased = middleReleased = rightReleased = false;

    x = 0.f;
    y = 0.f;

    index = id;
}


void FlxMouse::show() {
    BackendHolder::get().getBackend()->showMouse(true);
}


void FlxMouse::hide() {
    BackendHolder::get().getBackend()->showMouse(false);
}


void FlxMouse::updateState() {

    leftDown = BackendHolder::get().getBackend()->getMouseButtonState(0, index);
    middleDown = BackendHolder::get().getBackend()->getMouseButtonState(1, index);
    rightDown = BackendHolder::get().getBackend()->getMouseButtonState(2, index);

    // pressed
    if(leftDown && !lastLeftDown) leftPressed = true;
    else leftPressed = false;

    if(middleDown && !lastMiddleDown) middlePressed = true;
    else middlePressed = false;

    if(rightDown && !lastRightDown) rightPressed = true;
    else rightPressed = false;

    // released
    if(!leftDown && lastLeftDown) leftReleased = true;
    else leftReleased = false;

    if(!middleDown && lastMiddleDown) middleReleased = true;
    else middleReleased = false;

    if(!rightDown && lastRightDown) rightReleased = true;
    else rightReleased = false;

    // save position
    FlxVector pos = BackendHolder::get().getBackend()->getMousePosition(index);
    x = pos.x;
    y = pos.y;

    // save last frame buttons state
    lastLeftDown = leftDown;
    lastMiddleDown = middleDown;
    lastRightDown = rightDown;
}
