#include "FlxG.h"
#include "backend/sfml/Backend.h"

class MainState : public FlxState {

public:
    FlxSprite *player;
    FlxText *text;
    FlxGroup *obstacles;
    FlxTilemap *map;

    virtual void create() {
        FlxG::bgColor = 0xff9977aa;

        // map
        int lol[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

        map = new FlxTilemap();
        map->loadMap(lol, 28, 12, "data/Tilemap.png", 45, 45);
        add(map);

        // player
        player = new FlxSprite(100, 100);
        player->loadGraphic("data/player.png", 50, 50);

        std::vector<unsigned int> frames1;
        frames1.push_back(0);
        frames1.push_back(2);

        std::vector<unsigned int> frames2;
        frames2.push_back(1);
        frames2.push_back(3);

        player->addAnimation("anim1", frames1, 0.5);
        player->addAnimation("anim2", frames2, 0.5);
        player->play("anim2");

        add(player);


        FlxG::worldBounds = map->bounds;
        FlxG::followObject(player);


        // text
        text = new FlxText("Hello world!", "data/comic.ttf", 550, 100, 24, 0xff000000);
        text->angle = FlxU::degreesToRad(45);
        add(text);

        player->acceleration.y = 1;

        //FlxG::playMusic("data/3.ogg", 0.05f);
    }

    virtual void update() {

        player->velocity.x = 0;
        //player->velocity.y = 0;
        if(FlxG::key->down(FlxKey::Right)) player->velocity.x = 225;
        if(FlxG::key->down(FlxKey::Left)) player->velocity.x = -225;
        if(FlxG::key->pressed(FlxKey::Up)) player->velocity.y = -225;

        player->collide(map);

        if(FlxG::key->pressed(FlxKey::A)) player->visible = !player->visible;
        if(FlxG::key->pressed(FlxKey::S)) FlxG::play("data/ding.ogg");

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

    virtual void update(float p) {

        FlxPreloader::update(p);
    }
};


int main(int argc, char *argv[]) {
    FlxG::backend = new SFML_Backend();
    FlxG::preloader = new Preloader();

    return FlxG::setup("Hello world!", 800, 480, new MainState());
}
