#include "FlxKeyboard.h"
#include "backend/BackendHolder.h"

FlxKeyboard::FlxKeyboard() {
    for(unsigned int i = 0; i < 1024; i++) {
        lastState[i] = false;
    }
}

bool FlxKeyboard::down(FlxKey::KeyCode code) {
    return BackendHolder::get().getBackend()->isKeyDown(code);
}

bool FlxKeyboard::pressed(FlxKey::KeyCode code) {
    return down(code) && !lastState[code];
}

bool FlxKeyboard::released(FlxKey::KeyCode code) {
    return !down(code) && lastState[code];
}

void FlxKeyboard::updateState() {
    bool *state = BackendHolder::get().getBackend()->getKeysDown();

    for(unsigned int i = 0; i < 1024; i++) {
        lastState[i] = state[i];
    }
}
