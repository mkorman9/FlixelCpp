#include "FlxG.h"
#include "backend/sfml/Backend.h"

class MainState : public FlxState {

public:
    FlxSprite *player;
    FlxText *text;
    FlxTilemap *map;
    FlxButton *button;
    FlxEmitter *particles;

    virtual void create() {
        FlxG::bgColor = 0x9977aa;

        // map
        int lol[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
            0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
            0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

        map = new FlxTilemap();
        map->loadMap(lol, 28, 12, "data/Tilemap.png", 45, 45);
        add(map);

        // player
        player = new FlxSprite(100, 100);
        player->loadGraphic("data/player.png", 50, 50);
        player->alpha = 0.5f;

        std::vector<unsigned int> frames1;
        frames1.push_back(0);
        frames1.push_back(2);

        std::vector<unsigned int> frames2;
        frames2.push_back(1);
        frames2.push_back(3);

        player->addAnimation("anim1", frames1, 0.5);
        player->addAnimation("anim2", frames2, 0.5, false);
        player->play("anim1");

        add(player);


        FlxG::worldBounds = map->bounds;
        FlxG::followObject(player);


        // text
        text = new FlxText("", "data/comic.ttf", 550, 100, 24, 0x000000);
        text->angle = FlxU::PI / 4;  // PI/4 == 45 degrees
        add(text);

        // button
        button = new FlxButton(10, 10, "data/button.png", 160, 20, 3);
        button->setTextFormat("Close me!", "data/comic.ttf", 12, 0xffff00);
        button->onText->color = 0xff0000;
        add(button);

        // particle emitter
        particles = new FlxEmitter(0, 0, FlxVector(-50, 50), FlxVector(-50, 50), FlxVector(1, 2));
        particles->loadGraphic("data/part.png", 3, 3, 3);
        particles->gravity = 220;
        add(particles);

        player->acceleration.y = 220;
        FlxG::playMusic("data/3.ogg", 0.05f);
    }

    virtual void update() {

        player->velocity.x = 0;
        //player->velocity.y = 0;
        if(FlxG::key->down(FlxKey::Right)) player->velocity.x = 225;
        if(FlxG::key->down(FlxKey::Left)) player->velocity.x = -225;
        if(FlxG::key->pressed(FlxKey::Up) && player->isTouchingFloor(map)) player->velocity.y = -150;

        player->collide(map);
        particles->collide(map);

        if(FlxG::key->pressed(FlxKey::A)) player->visible = !player->visible;
        if(FlxG::key->pressed(FlxKey::S)) FlxG::play("data/ding.ogg");

        if(FlxG::key->pressed(FlxKey::Space)) {
            FlxG::flash(0xffffff, 0.2f);
        }

        if(FlxG::key->down(FlxKey::D)) {
            particles->atCenter(player);
            particles->emit(2);
        }

        if(button->released) FlxG::exitMessage = true;

        text->text = std::string("FPS: ") + FlxU::toString((int)FlxG::fps);
        FlxState::update();
    }
};


class Preloader : public FlxPreloader {

public:

    Preloader() {
        loadMusic("data/3.ogg");
        loadSound("data/ding.ogg");
    }

    virtual void create() {
        add(new FlxSprite(0, 0, "data/load.png"));

    }

    virtual void update() {
        FlxPreloader::update();
    }
};


int main(int argc, char *argv[]) {
    FlxG::backend = new SFML_Backend();
    FlxG::preloader = new Preloader();

    return FlxG::setup("Hello world!", 800, 480, new MainState());
}
