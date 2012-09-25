#include "FlxG.h"

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
std::vector<FlxMouse*> FlxG::mousesList;
FlxMouseHolder FlxG::mouse;
float FlxG::fps = 0;
float FlxG::fpsCounter = 0;
float FlxG::totalTime = 0;
float FlxG::fixedTime = 0.01f;
FlxSprite FlxG::flashSprite;
float FlxG::flashCounter = 0, FlxG::flashMaxTime = 0;
bool FlxG::flashing = false;
tween::Tweener FlxG::tweener;
FlxShadersList FlxG::shaders;
FlxState *FlxG::stateToSwitch = NULL;


// quick help function
extern int FlxPowerOf2(int input) {
    int value = 1;

    while (value < input) {
        value <<= 1;
    }

    return value;
}


/*
*  Main functions definitions starts here
*/
int FlxG::setup(const char *title, int Width, int Height, FlxState *state,
                const char *icon) {

    if(!backend) {
        std::cerr << "[Error] Backend is null" << std::endl;
        return 1;
    }

    width = Width;
    height = Height;

    backend->setupSurface(title, width, height, icon);

    FlxVector screenSize = backend->getScreenSize();
	screenWidth = screenSize.x;
	screenHeight = screenSize.y;

    key = new FlxKeyboard();
    srand(time(0));

    // flash screen sprite (texture size should be pow of 2)
    flashSprite.makeGraphic(FlxPowerOf2(width), FlxPowerOf2(height), 0xffffff);
    flashSprite.width = width;
    flashSprite.height = height;
    flashSprite.alpha = 0;

    // run preloader
    if(preloader) {
        preloader->create();
        backend->mainLoop(FlxPreloader::onUpdate, FlxPreloader::onDraw);

        delete preloader;
        FlxG::exitMessage = false;
    }

    switchState(state);

    // main loop
    backend->mainLoop(innerUpdate, innerDraw);


    if(state) {
        state->leave();
        delete state;
    }

    delete key;

    backend->exitApplication();
    return 0;
}

void FlxG::followObject(FlxObject *object) {
    toFollow = object;
}


void FlxG::switchState(FlxState *newState) {
    if(!newState) return;
    stateToSwitch = newState;
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

    for(unsigned int i = 0; i < mousesList.size(); i++) {

        #ifdef FLX_MOBILE
        if(mousesList[i]->leftReleased) {
            mousesList.erase(mousesList.begin() + i);
            continue;
        }

        if(mousesList[i]->leftPressed) {
            mousesList[i]->leftPressed = false;
        }
        #endif

        mousesList[i]->updateState();
    }
}


FlxBasic* FlxG::overlaps(FlxBasic *one, FlxBasic *two, const FlxBasic::CollisionCallback&
                         collisionCallback)
{
    return one->overlaps(two, collisionCallback);
}


FlxBasic* FlxG::collide(FlxBasic *one, FlxBasic *two, const FlxBasic::CollisionCallback&
                         collisionCallback)
{
    return one->collide(two, collisionCallback);
}


void FlxG::innerUpdate() {

    // switch state?
    if(stateToSwitch) {
        if(state) {
            state->leave();
            delete state;
        }

        shaders.clear();
        tweener.removeTween(NULL);
        worldBounds = { 0, 0, width, height };
        scroolVector = { 0, 0 };
        toFollow = NULL;

        state = stateToSwitch;
        state->create();

        stateToSwitch = NULL;
    }

    // sounds and music garbage collector
    for(unsigned int i = 0; i < FlxSound::Sounds.size(); i++) {
        if(FlxSound::Sounds[i]) {
            if(!FlxSound::Sounds[i]->isPlaying()) {
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
            if(!FlxMusic::Music[i]->isPlaying()) {
                delete FlxMusic::Music[i];
				FlxMusic::Music[i] = NULL;
                FlxMusic::Music.erase(FlxMusic::Music.begin() + i);
            }
        }
        else {
            FlxMusic::Music.erase(FlxMusic::Music.begin() + i);
        }
    }

    // update fps
    fpsCounter += elapsed;
    if(fpsCounter >= 1.f) {
        fps = 1.f / elapsed;
        fpsCounter = 0;
    }

    // update flashing screen stuff
    flashSprite.x = -scroolVector.x;
    flashSprite.y = -scroolVector.y;

    if(flashing) {

        flashCounter += fixedTime;

        if(flashCounter >= flashMaxTime) {
            flashing = false;
            flashCounter = flashMaxTime = 0;

            flashSprite.alpha = 0;
            flashSprite.color = 0xffffff;
        }
        else {
            flashSprite.alpha = flashCounter / flashMaxTime;
        }
    }

    // follow some object?
    if(toFollow) {
        FlxVector objectCenter = toFollow->getCenter();

		FlxVector move(objectCenter.x - (width / 2), objectCenter.y - (height / 2));

        if(move.x < worldBounds.x) move.x = worldBounds.x;
        if(move.x + width > worldBounds.width) move.x = worldBounds.width - width;

        if(move.y < worldBounds.y) move.y = worldBounds.y;
        if(move.y + height > worldBounds.height) move.y = worldBounds.height - height;

        scroolVector.x = -move.x;
        scroolVector.y = -move.y;
    }
    else {
        scroolVector.x = scroolVector.y = 0;
    }


    if(state) state->update();

    // update tweener
    tweener.step(int(totalTime * 1000));
    totalTime += fixedTime;

    // update input devices
    updateMouses();
    key->updateState();

    // handle flashing sprite
    if(flashing) flashSprite.update();
}


void FlxG::innerDraw() {
    if(state) state->draw();

    // draw shaders
    for(unsigned int i = 0; i < shaders.members.size(); i++) {
        if(shaders.members[i] && shaders.members[i]->data) {
            backend->drawShader(shaders.members[i]->data);
        }
    }

    // draw GUI
    if(state) state->drawGUI();

    // handle flashing sprite
    if(flashing) flashSprite.draw();
}


void FlxG::flash(int color, float time) {
    if(flashing) return;
    flashing = true;

    flashMaxTime = time;
    flashSprite.color = color;
}

