#include <FlxG.h>

#ifdef FLX_MOBILE
	#include <backend/sdl_mobile/Backend.h>
	#define Backend SDL_Mobile_Backend
#else
	#include <backend/sfml/Backend.h>
	#define Backend SFML_Backend
#endif


/* 
* Main application state.
* Flixel application could contain many different states. For example:
*	- Menu
*	- Gameplay
*	- Splash screen
*
* You can simply switch states using FlxG::switchState(...) function.
*/
class MainState : public FlxState {

public:

	/*
	*  This function is called once when state is set with FlxG::switchState(...)
	*/
    virtual void create() {
	
        FlxG::bgColor = 0x9977aa;  // Set background color to some random value
		
    }
	
	
	/*
	*  This function is called every frame.
	*  Update your game logic here.
	*/
    virtual void update() {
	
		// Exit game if user press Escape button (or BACK button on Android devices)
		if(FlxG::key->pressed(FlxKey::Escape)) FlxG::exitMessage = true;
		
    }
	
	
	/*
	*  This function is called once when state is being destroyed (but before class destructor)
	*/
    virtual void leave() {
	
		// do nothing :)
		
    }
};



int main(int argc, char *argv[]) {
    FlxG::backend = new Backend(); // remember to always set backend

	// initialize game window with 800x480px resolution
    int ret = FlxG::setup("Sample application", 800, 480, new MainState());
    exit(ret);
}

