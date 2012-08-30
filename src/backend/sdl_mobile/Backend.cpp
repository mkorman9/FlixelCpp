#include "backend/sdl_mobile/Backend.h"
#include "backend/BackendHolder.h"
#include "FlxG.h"

/*
* SDL image class
*/
class SDL_Image : public FlxBackendImage {

public:
    SDL_Texture *texture;
	int width, height;

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    int getFormat() {
        return 0; // default
    }
};



/*
*  Main backend class definition
*/
bool SDL_Mobile_Backend::setupSurface(const char *title, int width, int height) {

    // initialize SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	// initialize addtional libraries
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();
	Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD);
	
    // create the window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	SDL_SetWindowFullscreen(window, SDL_TRUE);
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	// open audio device
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096;
	
	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
  
    for(int i = 0; i < 1024; i++) {
        keysDown[i] = false;
    }
	
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0, &mode);
	screenWidth = mode.w;
	screenHeight = mode.h;
				
	exitMsg = false;
    return true;
}

void SDL_Mobile_Backend::mainLoop(void (*onUpdate)(), void (*onDraw)()) {

    float currentTime = (float)SDL_GetTicks() / 1000.f;
    float accumulator = 0;

    while(!FlxG::exitMessage && !exitMsg) {

        // fixed timestep stuff
        float newTime = (float)SDL_GetTicks() / 1000.f;
        float elapsed = newTime - currentTime;
        currentTime = newTime;

        accumulator += elapsed;

        while(accumulator >= FlxG::fixedTime) {

            // update all stuff
            updateEvents();
            onUpdate();

            accumulator -= FlxG::fixedTime;
        }

		SDL_SetRenderDrawColor(renderer, COLOR_GET_R(FlxG::bgColor), COLOR_GET_G(FlxG::bgColor),
                        COLOR_GET_B(FlxG::bgColor), 255);
		SDL_RenderClear(renderer);
		
		onDraw();
		
		SDL_RenderPresent(renderer);
		
        FlxG::elapsed = elapsed;
    }
}

FlxVector SDL_Mobile_Backend::getScreenSize() {
    return FlxVector((float)screenWidth, (float)screenHeight);
}

void SDL_Mobile_Backend::exitApplication() {

	for(std::map<std::string, FlxBackendImage*>::iterator it = images.begin(); it != images.end(); it++) {
		if(it->second) {
			SDL_Image *img = (SDL_Image*)it->second;
			
			if(img->texture) SDL_DestroyTexture(img->texture);
			delete img;
		}
	}
	
	for(std::map<std::string, void*>::iterator it = fonts.begin(); it != fonts.end(); it++) {
		if(it->second) {
			TTF_Font *font = (TTF_Font*)it->second;
			if(font) TTF_CloseFont(font);
		}
	}
	
    for(std::map<std::string, FlxBackendMusic*>::iterator it = music.begin(); it != music.end(); it++) {
        FlxBackendMusic *m = (FlxBackendMusic*) it->second;
 
    }
	
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
    SDL_Quit();
}

bool* SDL_Mobile_Backend::getKeysDown() {
    return keysDown;
}

bool SDL_Mobile_Backend::isKeyDown(int code) {
    return keysDown[code];
}

void SDL_Mobile_Backend::updateEvents() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
    
		if(event.type == SDL_WINDOWEVENT_CLOSE || event.type == SDL_QUIT) {
			exitMsg = true;
        }
	
		// finger down
		else if(event.type == SDL_FINGERDOWN) {
			SDL_Touch *touch = SDL_GetTouch(event.tfinger.touchId);
			FlxMouse::onTouchBegin(event.tfinger.fingerId, ((float)event.tfinger.x / (float)touch->xres) * screenWidth * FlxG::screenScaleVector.x, 
				((float)event.tfinger.y / (float)touch->yres) * screenHeight * FlxG::screenScaleVector.y);
		}
		
		// finger up
		else if(event.type == SDL_FINGERUP) {
			SDL_Touch *touch = SDL_GetTouch(event.tfinger.touchId);
			
			FlxMouse::onTouchEnd(event.tfinger.fingerId, ((float)event.tfinger.x / (float)touch->xres) * screenWidth * FlxG::screenScaleVector.x, 
				((float)event.tfinger.y / (float)touch->yres) * screenHeight * FlxG::screenScaleVector.y);
		}
		
		// key down
		else if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_AC_BACK) keysDown[FlxKey::BackButton] = true;
		}
		
		// key up
		else if(event.type == SDL_KEYUP) {
			if(event.key.keysym.sym == SDLK_AC_BACK) keysDown[FlxKey::BackButton] = false;
		}
    }
}

FlxVector SDL_Mobile_Backend::getMousePosition(int index) {
    return FlxVector(0, 0);
}

bool SDL_Mobile_Backend::getMouseButtonState(int button, int index) {
    return false;
}


void SDL_Mobile_Backend::showMouse(bool show) {
    // no action
}

void SDL_Mobile_Backend::drawImage(FlxBackendImage *image, float x, float y,  FlxVector scale, float angle,
                             FlxRect source, int color, bool flipped, bool scrool, float alpha)
{
	if(!image) return;
	
	SDL_Image *img = (SDL_Image*) image;
	if(!img->texture) return;
	
	if(scrool) {
		x += FlxG::scroolVector.x;
		y += FlxG::scroolVector.y;
	}
	
	if(FlxG::scaleToScreen) {
		x *= FlxG::screenScaleVector.x;
		y *= FlxG::screenScaleVector.y;
		scale.x *= FlxG::screenScaleVector.x;
		scale.y *= FlxG::screenScaleVector.y;
	}
	
	x += source.width - (scale.x * source.width);
	y += source.height - (scale.y * source.height);
	
	SDL_Rect srcRect = { source.x, source.y, source.width, source.height };
	SDL_Rect destRect = { x, y, source.width * scale.x, source.height * scale.y };
	
	SDL_SetTextureColorMod(img->texture, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color));
	SDL_SetTextureAlphaMod(img->texture, int(alpha * 255.f));
	SDL_RenderCopyEx(renderer, img->texture, &srcRect, &destRect, -FlxU::radToDegrees(angle), NULL, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

FlxBaseText *SDL_Mobile_Backend::createText(const char *text, void *font, int size, FlxVector scale, float angle,
                                   int color, float alpha)
{
	if(!font) return NULL;
	
	SDL_Color colour = { COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha * 255.f };
	SDL_Surface *txtSurface = TTF_RenderText_Solid((TTF_Font*)font, text, colour);
	
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, txtSurface);
	SDL_FreeSurface(txtSurface);
	
	int w = 0, h = 0;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h); 
	
	FlxBaseText *data = new FlxBaseText();
	data->data = tex;
    data->font = font;
    data->size = size;
    data->scale = scale;
    data->angle = angle;
    data->color = color;
    data->alpha = alpha;
    data->text = text;
    data->bounds.x = (float)w;
    data->bounds.y = (float)h;
	
	return data;
}

void SDL_Mobile_Backend::destroyText(FlxBaseText *data) {

    if(data) {
		if(data->data) SDL_DestroyTexture((SDL_Texture*)data->data);
        delete data;
    }
}

void SDL_Mobile_Backend::drawText(FlxBaseText *text, float x, float y, bool scrool) {

	if(!text) return;
	
	SDL_Texture *tex = (SDL_Texture*) text->data;
	if(!tex) return;
	
	if(scrool) {
		x += FlxG::scroolVector.x;
		y += FlxG::scroolVector.y;
	}
	
	FlxVector scale = text->scale;
	
	if(FlxG::scaleToScreen) {
		x *= FlxG::screenScaleVector.x;
		y *= FlxG::screenScaleVector.y;
		scale.x *= FlxG::screenScaleVector.x;
		scale.y *= FlxG::screenScaleVector.y;
	}
	
	x += int(text->bounds.x - (scale.x * text->bounds.x));
	y += int(text->bounds.y - (scale.y * text->bounds.y));
	
	SDL_Rect srcRect = { 0, 0, int(text->bounds.x), int(text->bounds.y) };
	SDL_Rect destRect = { x, y, int(text->bounds.x * scale.x), int(text->bounds.y * scale.y) };
	
	SDL_RenderCopyEx(renderer, tex, &srcRect, &destRect, -FlxU::radToDegrees(text->angle), NULL, SDL_FLIP_NONE);
}

FlxBackendImage* SDL_Mobile_Backend::createImage(int width, int height, int color, float alpha) {

    return NULL;
}

FlxBackendImage *SDL_Mobile_Backend::loadImage(const char *path) {

    if(images.find(path) != images.end()) {
        return images[path];
    }

	SDL_Image *img = new SDL_Image();
	img->texture = IMG_LoadTexture(renderer, path);
	
	if(img->texture) {
		SDL_QueryTexture(img->texture, NULL, NULL, &img->width, &img->height); 
		images[path] = img;
	}
	
    return img;
}

void *SDL_Mobile_Backend::loadFont(const char *path, int fontSize) {

    std::stringstream ss;
    ss << path << "__size_" << fontSize;

    if(fonts.find(ss.str()) != fonts.end()) {
        return fonts[ss.str()];
    }

	TTF_Font *font = TTF_OpenFont(path, fontSize);
	if(font) {
		fonts[ss.str()] = font;
	}
	
    return font;
}

void* SDL_Mobile_Backend::loadSound(const char *path) {

    if(sounds.find(path) != sounds.end()) {
        return sounds[path];
    }


    return NULL;
}

FlxBackendMusic* SDL_Mobile_Backend::loadMusic(const char *path) {

    if(music.find(path) != music.end()) {
        return music[path];
    }

    return NULL;
}

FlxBackendSound* SDL_Mobile_Backend::playSound(void *sound, float vol) {


    return NULL;
}

void SDL_Mobile_Backend::playMusic(FlxBackendMusic *buff, float vol) {

    
}

// android/iphone data saving
void SDL_Mobile_Backend::saveData(const char *path, const std::map<std::string, std::string>& data) {


}

bool SDL_Mobile_Backend::loadData(const char *path, std::map<std::string, std::string>& data) {

    return true;
}

