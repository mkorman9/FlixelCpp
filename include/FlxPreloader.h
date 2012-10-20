/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_PRELOADER_H_
#define _FLX_PRELOADER_H_

#include "FlxState.h"
#include "backend/cpp.h"

/**
*  Loading state flags
*/
enum FlxLoadingState {
    FLX_IMAGES_LOADING,
    FLX_FONTS_LOADING,
    FLX_MUSIC_LOADING,
    FLX_SOUNDS_LOADING
};


/**
*  Resource loading helper
*/
class FlxPreloader : public FlxState {

private:
    std::vector<std::string> imagesToLoad;
    std::vector<std::pair<std::string, int> > fontsToLoad;
    std::vector<std::string> musicToLoad;
    std::vector<std::string> soundsToLoad;

    int currentIterator;
    unsigned int assetsLoaded;
public:

	/**
	*  Current instance of preloader (Internal! Do not touch!)
	*/
    static FlxPreloader *CurrentInstance;

	/**
	*  Current state of loading
	*/
    FlxLoadingState state;
	
	/**
	*  Loading progress in percents
	*/
    float percent;


	/**
	*  Default constructor
	*/
    FlxPreloader() {
        state = FLX_IMAGES_LOADING;
        CurrentInstance = this;
        currentIterator = 0;
        assetsLoaded = 0;
    }
	
	/**
	*  Default destructor
	*/
    ~FlxPreloader() {
        clear();
    }

	/**
	*  Create event (to override)
	*/
    virtual void create() {
    }

	/**
	*  Add new image to loading queue
	*  @param path Path to image file (must be in internal device's storage)
	*/
    void loadImage(const std::string& path) {
        imagesToLoad.push_back(path);
    }
	
	/**
	*  Add new font to loading queue
	*  @param path Path to font file (must be in internal device's storage)
	*  @param size Font height
	*/
    void loadFont(const std::string& path, int size) {
        fontsToLoad.push_back(std::make_pair(path, size));
    }
	
	/**
	*  Add new music stream to loading queue.
	*  <b>Note: Whole music file is not loaded to memory. Music in FlixelCpp is streamed dynamically</b> 
	*  @param path Path to music file (must be in internal device's storage)
	*/
    void loadMusic(const std::string& path) {
        musicToLoad.push_back(path);
    }
	
	/**
	*  Add new sound to loading queue.
	*  @param path Path to sound file (must be in internal device's storage)
	*/
    void loadSound(const std::string& path) {
        soundsToLoad.push_back(path);
    }
	
	/**
	*  Error handler (should be overrided)
	*  @param resourceName Resource which caused an error
	*/
    virtual void onError(const std::string& resourceName) {
        (void)resourceName;
    }
	
	/**
	*  Update event (to override)
	*/
    virtual void update();
	
	/**
	*  Draw event (to override)
	*/
    virtual void draw();

	
    static void onUpdate();
    static void onDraw();
};

#endif


