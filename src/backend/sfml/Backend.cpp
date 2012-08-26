#include "Backend.h"
#include "../BackendHolder.h"
#include "../../FlxU.h"
#include <fstream>

/*
* SFML image class
*/
class SFML_Image : public FlxBackendImage {

public:
    sf::Image Graphic;

    int getWidth() {
        return Graphic.GetWidth();
    }

    int getHeight() {
        return Graphic.GetHeight();
    }

    int getFormat() {
        return 0; // default
    }
};

/*
*  SFML Sound class
*/
class SFML_Sound : public FlxBackendSound {

public:
    sf::Sound Track;

    virtual ~SFML_Sound() {
        stop();
    }

    virtual void play() {
        Track.Play();
    }

    virtual void stop() {
        Track.Stop();
    }

    virtual void pause() {
        Track.Pause();
    }

    virtual void setLoop(bool t) {
        Track.SetLoop(t);
    }

    virtual void setVolume(float vol) {
        vol *= 100.f;
    }

    virtual bool isPlaying() {
        return Track.GetStatus() != sf::Sound::Stopped;
    }

    virtual bool isPaused() {
        return Track.GetStatus() == sf::Sound::Paused;
    }
};

/*
*  SFML Music class
*/
class SFML_Music : public FlxBackendMusic {

public:
    sf::Music Track;

    virtual ~SFML_Music() {
        stop();
    }

    virtual void play() {
        Track.Play();
    }

    virtual void stop() {
        Track.Stop();
    }

    virtual void pause() {
        Track.Pause();
    }

    virtual void setLoop(bool t) {
        Track.SetLoop(t);
    }

    virtual void setVolume(float vol) {
        vol *= 100.f;
        Track.SetVolume(vol);
    }

    virtual bool isPlaying() {
        return Track.Playing;
    }

    virtual bool isPaused() {
        return Track.Paused;
    }
};


/*
*  Main backend class definition
*/
bool SFML_Backend::setupSurface(const char *title, int width, int height) {

    exitMsg = false;

    window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    if(!window) return false;

    window->EnableKeyRepeat(false);
    for(int i = 0; i < 1024; i++) {
        keysDown[i] = false;
    }

    touchBegin(0, window->GetInput().GetMouseX(), window->GetInput().GetMouseY());
    clock.Reset();

    return true;
}

void SFML_Backend::setCallbacks(void (*onTouchBegin)(int id, float, float), void (*onTouchEnd)(int id, float, float)) {
    touchBegin = onTouchBegin;
    touchEnd = onTouchEnd;
}

FlxVector SFML_Backend::getScreenSize() {
    sf::VideoMode screen = sf::VideoMode::GetDesktopMode();
    return FlxVector(screen.Width, screen.Height);
}

bool SFML_Backend::exitMessage() {
    return exitMsg;
}

void SFML_Backend::exitApplication() {

    for(std::map<std::string, void*>::iterator it = sounds.begin(); it != sounds.end(); it++) {
        sf::SoundBuffer *sound = (sf::SoundBuffer*) it->second;
        delete sound;
    }

    for(std::map<std::string, FlxBackendMusic*>::iterator it = music.begin(); it != music.end(); it++) {
        FlxBackendMusic *m = (FlxBackendMusic*) it->second;
        delete m;
    }

    touchEnd(0, 0, 0);

    window->Close();
    delete window;
}

bool* SFML_Backend::getKeysDown() {
    return keysDown;
}

bool SFML_Backend::isKeyDown(int code) {
    return window->GetInput().IsKeyDown((sf::Key::Code)code);
}

float SFML_Backend::getSystemTime() {
    return (float)clock.GetElapsedTime();
}

void SFML_Backend::updateInput() {

    sf::Event event;
    while (window->GetEvent(event)) {

        // window closed
        if(event.Type == sf::Event::Closed) {
            exitMsg = true;
        }

        // keyboard events
        else if(event.Type == sf::Event::KeyPressed) {
            keysDown[event.Key.Code] = true;
        }
        else if(event.Type == sf::Event::KeyReleased) {
            keysDown[event.Key.Code] = false;
        }
    }
}

FlxVector SFML_Backend::getMousePosition(int index) {
    return FlxVector(window->GetInput().GetMouseX(), window->GetInput().GetMouseY());
}

bool SFML_Backend::getMouseButtonState(int button, int index) {

    if(button == 0) {
        return window->GetInput().IsMouseButtonDown(sf::Mouse::Left);
    }
    else if(button == 1) {
        return window->GetInput().IsMouseButtonDown(sf::Mouse::Middle);
    }
    else if(button == 2) {
        return window->GetInput().IsMouseButtonDown(sf::Mouse::Right);
    }

    return false;
}


void SFML_Backend::showMouse(bool show) {
    window->ShowMouseCursor(show);
}

void SFML_Backend::beginScene(int color) {
    window->Clear(sf::Color(COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), 255));
}

void SFML_Backend::drawImage(FlxBackendImage *img, float x, float y,  FlxVector scale, float angle,
                             FlxRect source, int color, bool flipped, bool scrool, float alpha)
{
    SFML_Image *gfx = (SFML_Image*)img;

    FlxVector move = BackendHolder::get().getScroolVector();
    if(!scrool) { move.x = move.y = 0; }

    sf::Sprite sprite;
    sprite.SetImage(gfx->Graphic);
    sprite.SetPosition(x + (source.width / 2) + move.x, y + (source.height / 2) + move.y);
    sprite.SetCenter((source.width / 2), (source.height / 2));
    sprite.SetSubRect(sf::IntRect(source.x, source.y, source.x + source.width, source.y + source.height));
    sprite.SetRotation(-FlxU::radToDegrees(angle));
    sprite.SetScale(scale.x, scale.y);
    sprite.FlipX(flipped);
    sprite.SetColor(sf::Color(COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha * 255.f));

    window->Draw(sprite);
}

FlxVector SFML_Backend::drawText(const char *text, void *font, int size, float x, float y, FlxVector scale, float angle, int color,
                            bool scrool, float alpha)
{
    if(!font) return FlxVector(0, 0);

    sf::String str;
    str.SetFont(*((sf::Font*)font));
    str.SetText(text);
    str.SetSize(size);

    sf::FloatRect rect = str.GetRect();
    FlxVector move = BackendHolder::get().getScroolVector();
    if(!scrool) { move.x = move.y = 0; }

    str.SetCenter(rect.GetWidth() / 2, rect.GetHeight() / 2);
    str.SetPosition(x + (rect.GetWidth() / 2) + move.x, y + (rect.GetHeight() / 2) + move.y);
    str.SetScale(scale.x, scale.y);
    str.SetRotation(-FlxU::radToDegrees(angle));
    str.SetColor(sf::Color(COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha * 255.f));

    window->Draw(str);

    return FlxVector(rect.GetWidth(), rect.GetHeight());;
}

void SFML_Backend::endScene() {
    window->Display();
}

FlxBackendImage* SFML_Backend::createImage(int width, int height, int color, float alpha) {
    SFML_Image *img = new SFML_Image();
    img->Graphic.Create(width, height, sf::Color(COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color),
                                                 alpha * 255.f));
    img->Graphic.SetSmooth(false);

    return img;
}

FlxBackendImage *SFML_Backend::loadImage(const char *path) {

    if(images.find(path) != images.end()) {
        return images[path];
    }

    SFML_Image *img = new SFML_Image();
    img->Graphic.LoadFromFile(path);
    img->Graphic.SetSmooth(false);
    images[path] = img;

    return img;
}

void *SFML_Backend::loadFont(const char *path, int fontSize) {

    std::stringstream ss;
    ss << path << "__size_" << fontSize;

    if(fonts.find(ss.str()) != fonts.end()) {
        return fonts[ss.str()];
    }

    sf::Font *font = new sf::Font();
    font->LoadFromFile(path, fontSize);
    fonts[ss.str()] = font;

    return font;
}

void* SFML_Backend::loadSound(const char *path) {

    if(sounds.find(path) != sounds.end()) {
        return sounds[path];
    }

    sf::SoundBuffer *buffer = new sf::SoundBuffer();
    buffer->LoadFromFile(path);
    sounds[path] = buffer;

    return buffer;
}

FlxBackendMusic* SFML_Backend::loadMusic(const char *path) {

    if(music.find(path) != music.end()) {
        return music[path];
    }

    SFML_Music *m = new SFML_Music();
    m->Track.OpenFromFile(path);
    music[path] = m;

    return m;
}

FlxBackendSound* SFML_Backend::playSound(void *sound, float vol) {

    sf::SoundBuffer *buffer = (sf::SoundBuffer*) sound;

    SFML_Sound *s = new SFML_Sound();
    s->Track.SetBuffer(*buffer);
    s->setVolume(vol);

    s->play();

    return s;
}

void SFML_Backend::playMusic(FlxBackendMusic *buff, float vol) {

    SFML_Music *m = (SFML_Music*) buff;
    m->setVolume(vol);
    m->play();
}

// standard PC data saving
void SFML_Backend::saveData(const char *path, const std::map<std::string, std::string>& data) {

    std::ofstream stream(path);
    if(!stream) return;

    std::string rawData;
    for(std::map<std::string, std::string>::const_iterator it = data.begin(); it != data.end(); it++) {
        rawData += it->first + '\n' + it->second + '\n';
    }

    // encode data to prevent manual save changes
    // note: this is not an encryption!
    for(unsigned int i = 0; i < rawData.size(); i++) {
        rawData[i] = rawData[i] ^ 24;
    }

    stream.write(rawData.data(), rawData.size());
    stream.close();
}

bool SFML_Backend::loadData(const char *path, std::map<std::string, std::string>& data) {

    std::ifstream stream(path);
    if(!stream) return false;

    std::string rawData;
    while(!stream.eof()) {
        rawData += stream.get() ^ 24;
    }

    rawData = rawData.substr(0, rawData.size() - 1);

    // parse data
    std::stringstream ss(rawData);
    std::string name, value;

    while(!ss.eof()) {

        if(name == "") {
            std::getline(ss, name);
        }
        else {
            std::getline(ss, value);

            data[name] = value;
            name = value = "";
        }
    }

    return true;
}

