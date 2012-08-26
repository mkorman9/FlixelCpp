#include "FlxG.h"
#include "backend/BackendHolder.h"

FlxState *FlxG::state;
float FlxG::elapsed;
bool FlxG::exitMessage = false;
FlxBackendBase *FlxG::backend;
int FlxG::bgColor = 0xff000000;
FlxKeyboard *FlxG::key;
int FlxG::width, FlxG::height;
int FlxG::screenWidth, FlxG::screenHeight;
FlxPreloader *FlxG::preloader = NULL;
FlxMusic *FlxG::music = 0;
FlxRect FlxG::worldBounds;
FlxVector FlxG::scroolVector;
FlxObject *FlxG::toFollow = NULL;
std::vector<FlxMouse*> FlxG::mouse;

int FlxG::setup(const char *title, int Width, int Height, FlxState *state) {

    if(!backend) {
        std::cerr << "[Error] Backend is null" << std::endl;
        return 1;
    }

    width = Width;
    height = Height;

    BackendHolder::get().setBackend(backend);
    BackendHolder::get().getBackend()->setCallbacks(&FlxMouse::onTouchBegin, &FlxMouse::onTouchEnd);
    BackendHolder::get().getBackend()->setupSurface(title, width, height);

    screenWidth = BackendHolder::get().getBackend()->getScreenSize().x;
    screenHeight = BackendHolder::get().getBackend()->getScreenSize().y;
    BackendHolder::get().setScalingRatio(screenWidth / width, screenHeight / height);

    key = new FlxKeyboard();
    srand(time(0));

    // run preloader
    if(preloader) {
        preloader->create();
        preloader->run();
    }

    switchState(state);

    // main loop
    while(!backend->exitMessage() && !exitMessage) {

        // sounds and music garbage collector
        for(unsigned int i = 0; i < FlxSound::Sounds.size(); i++) {
            if(FlxSound::Sounds[i]) {
                if(!FlxSound::Sounds[i]->isPlaying() && !FlxSound::Sounds[i]->isPaused()) {
                    delete FlxSound::Sounds[i];
                    FlxSound::Sounds.erase(FlxSound::Sounds.begin() + i);
                }
            }
            else {
                FlxSound::Sounds.erase(FlxSound::Sounds.begin() + i);
            }
        }

        for(unsigned int i = 0; i < FlxMusic::Music.size(); i++) {
            if(FlxMusic::Music[i]) {
                if(!FlxMusic::Music[i]->isPlaying() && !FlxMusic::Music[i]->isPaused()) {
                    delete FlxMusic::Music[i];
                    FlxMusic::Music.erase(FlxMusic::Music.begin() + i);
                }
            }
            else {
                FlxMusic::Music.erase(FlxMusic::Music.begin() + i);
            }
        }

        elapsed = BackendHolder::get().getBackend()->getDeltaTime();
        BackendHolder::get().getBackend()->updateInput();

        update();

        BackendHolder::get().getBackend()->beginScene(bgColor);
        draw();
        BackendHolder::get().getBackend()->endScene();

        updateMouses();
        key->updateState();
    }

    delete key;

    BackendHolder::get().getBackend()->exitApplication();
    return 0;
}

void FlxG::followObject(FlxObject *object) {
    toFollow = object;
}


void FlxG::setTimeModifier(float mod) {
    BackendHolder::get().setTimeModifier(mod);
}


void FlxG::switchState(FlxState *newState) {
    if(!newState) return;
    if(state) delete state;

    state = newState;
    state->create();
}


FlxSound FlxG::play(const char *path, float vol) {
    FlxSound *s = new FlxSound(path);
    s->play(vol);
    return *s;
}


FlxMusic* FlxG::playMusic(const char *path, float vol) {
    FlxMusic *s = new FlxMusic(path);
    s->play(vol);

    music = s;
    return s;
}


void FlxG::updateMouses() {

    for(unsigned int i = 0; i < mouse.size(); i++) {

        #ifdef FLX_MOBILE
        if(mouse[i]->leftReleased) {
            mouse.erase(mouse.begin() + i);
            continue;
        }

        if(mouse[i]->leftPressed) {
            mouse[i]->leftPressed = false;
        }
        #endif

        mouse[i]->updateState();
    }
}


void FlxG::update() {

    // follow some object?
    if(toFollow) {
        FlxVector objectCenter = toFollow->getCenter();
        FlxVector move(objectCenter.x - (width / 2), objectCenter.y - (height / 2));

        if(move.x < worldBounds.x) move.x = worldBounds.x;
        if(move.x + width > worldBounds.width) move.x = worldBounds.width - width;

        if(move.y < worldBounds.y) move.y = worldBounds.y;
        if(move.y + height > worldBounds.height) move.y = worldBounds.height - height;

        scroolVector = move;
        BackendHolder::get().setScrool(move);
    }
    else {
        scroolVector = FlxVector(0,0);
        BackendHolder::get().setScrool(scroolVector);
    }


    if(state) state->update();
}


void FlxG::draw() {
    if(state) state->draw();
}


void FlxG::flash(int color, float time) {
    // TODO
}
