#include "glew/glew.h"
#include "backend/sfml/Backend.h"
#include "FlxU.h"
#include "FlxG.h"

// default vertex shader
const GLchar DefaultVertexShader[] = \
    "varying vec2 TexCoords;\n"
    "\n"
    "void main()\n"
    "{\n"
       "gl_Position = gl_ProjectionMatrix * gl_Vertex;\n"
       "TexCoords   = gl_MultiTexCoord0;\n"
    "}\n";


extern int FlxPowerOf2(int input);


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
*  SFML shader class
*/
class SFML_Shader : public FlxBackendShader {

public:
    GLint shaderProgram, vertexShader, fragmentShader;
    std::map<std::string, GLint> textures;

    virtual ~SFML_Shader() {
        glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteProgram(shaderProgram);
    }

    virtual void setParameter(const char *name, float x) {
        glUseProgram(shaderProgram);
		GLint location = glGetUniformLocation(shaderProgram, name);

		if(location != -1) {
		    glUniform1f(location, x);
        }

		glUseProgram(0);
    }

    virtual void setParameter(const char *name, float x, float y) {
        glUseProgram(shaderProgram);
		GLint location = glGetUniformLocation(shaderProgram, name);

		if(location != -1) {
		    glUniform2f(location, x, y);
        }

		glUseProgram(0);
    }

    virtual void setParameter(const char *name, float x, float y, float z) {
        glUseProgram(shaderProgram);
		GLint location = glGetUniformLocation(shaderProgram, name);

		if(location != -1) {
		    glUniform3f(location, x, y, z);
        }

		glUseProgram(0);
    }

    virtual void setParameter(const char *name, float x, float y, float z, float w) {
        glUseProgram(shaderProgram);
		GLint location = glGetUniformLocation(shaderProgram, name);

		if(location != -1) {
		    glUniform4f(location, x, y, z, w);
        }

		glUseProgram(0);
    }

    virtual void setParameter(const char *name, FlxBackendImage *i) {
        if(i) {
            SFML_Image *img = (SFML_Image*) i;
            img->Graphic.Bind();

            int tex;
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex);

            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            textures[name] = tex;
        }
        else {
            textures[name] = -1;
        }
    }
};


class SFML_File : public FlxBackendFile {

private:
    FILE *filePtr;
public:
    virtual ~SFML_File() {
        close();
    }

    virtual bool open(const char *path, const char *mode, bool internal) {
        (void)internal;

        filePtr = fopen(path, mode);
        return filePtr != NULL;
    }

    virtual bool eof() {
        return feof(filePtr) != 0;
    }

    virtual unsigned int tell() {
        return ftell(filePtr);
    }

    virtual void seek(long offset, int origin) {
        fseek(filePtr, offset, origin);
    }

    virtual void write(const char *data, unsigned int size) {
        fwrite(data, 1, size, filePtr);
    }

    virtual int read(char *data, unsigned int maxSize) {
        return fread(data, 1, maxSize, filePtr);
    }

    virtual void close() {
        fclose(filePtr);
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

    virtual void setLoop(bool t) {
        Track.SetLoop(t);
    }

    virtual void setVolume(float vol) {
        vol *= 100.f;
    }

    virtual bool isPlaying() {
        return Track.GetStatus() != sf::Sound::Stopped;
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

    virtual void setLoop(bool t) {
        Track.SetLoop(t);
    }

    virtual void setVolume(float vol) {
        vol *= 100.f;
        Track.SetVolume(vol);
    }

    virtual bool isPlaying() {
		return Track.GetStatus() != sf::Sound::Stopped;
    }
};



/*
*  Main backend class definition
*/
SFML_Backend::SFML_Backend(bool f) {
    fullscreen = f;
}

bool SFML_Backend::setupSurface(const char *title, int width, int height, const char *icon) {

    unsigned long style = sf::Style::Resize | sf::Style::Close;
    if(fullscreen) style = sf::Style::Fullscreen;

    window = new sf::RenderWindow(sf::VideoMode(width, height), title, style);
    if(!window) return false;

    window->EnableKeyRepeat(false);
    for(int i = 0; i < 1024; i++) {
        keysDown[i] = false;
    }

    if(icon) {
        sf::Image iconImg;
        if(iconImg.LoadFromFile(icon)) {
            window->SetIcon(iconImg.GetWidth(), iconImg.GetHeight(), iconImg.GetPixelsPtr());
        }
    }

    FlxMouse::onTouchBegin(0, (float)window->GetInput().GetMouseX(), (float)window->GetInput().GetMouseY());
    clock.Reset();

    // create framebuffer if needed
    if(isShadersSupported()) {
        unsigned char *pixels = new unsigned char[FlxPowerOf2(width) * FlxPowerOf2(height) * 3];
        for(unsigned int i = 0; i < sizeof(pixels); i++) pixels[i] = 255;

        glGenTextures(1, &framebuffer);
		glBindTexture(GL_TEXTURE_2D, framebuffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, FlxPowerOf2(width), FlxPowerOf2(height), 0, GL_RGB,
               GL_UNSIGNED_BYTE, pixels);

        delete[] pixels;
    }

    glewInit();
    return true;
}

void SFML_Backend::mainLoop(void (*onUpdate)(), void (*onDraw)()) {

    float currentTime = (float)clock.GetElapsedTime();
    float accumulator = 0;

    while(window->IsOpened() && !FlxG::exitMessage) {

        // fixed timestep stuff
        float newTime = (float)clock.GetElapsedTime();
        float elapsed = newTime - currentTime;
        currentTime = newTime;

        accumulator += elapsed;

        while(accumulator >= FlxG::fixedTime) {

            // update all stuff
            updateEvents();
            onUpdate();

            accumulator -= FlxG::fixedTime;
        }

        // render
        window->Clear(sf::Color(COLOR_GET_R(FlxG::bgColor), COLOR_GET_G(FlxG::bgColor),
                        COLOR_GET_B(FlxG::bgColor), 255));
        onDraw();
        window->Display();

        FlxG::elapsed = elapsed;
    }
}

FlxVector SFML_Backend::getScreenSize() {
    sf::VideoMode screen = sf::VideoMode::GetDesktopMode();
    return FlxVector((float)screen.Width, (float)screen.Height);
}

void SFML_Backend::exitApplication() {

    glDeleteTextures(1, &framebuffer);

    for(std::map<std::string, void*>::iterator it = sounds.begin(); it != sounds.end(); it++) {
        sf::SoundBuffer *sound = (sf::SoundBuffer*) it->second;
        delete sound;
    }

    for(std::map<std::string, FlxBackendMusic*>::iterator it = music.begin(); it != music.end(); it++) {
        FlxBackendMusic *m = (FlxBackendMusic*) it->second;
        delete m;
    }

    for(unsigned int i = 0; i < shaders.size(); i++) {
        if(shaders[i]) delete shaders[i];
    }

    FlxMouse::onTouchEnd(0, 0, 0);

    window->Close();
    delete window;
}

bool* SFML_Backend::getKeysDown() {
    return keysDown;
}

bool SFML_Backend::isKeyDown(int code) {
    return window->GetInput().IsKeyDown((sf::Key::Code)code);
}

void SFML_Backend::updateEvents() {

    sf::Event event;
    while (window->GetEvent(event)) {

        // window close
        if(event.Type == sf::Event::Closed) {
            FlxG::exitMessage = true;
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
    (void)index;
    return FlxVector((float)window->GetInput().GetMouseX(), (float)window->GetInput().GetMouseY());
}

bool SFML_Backend::getMouseButtonState(int button, int index) {
    (void)index;

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

void SFML_Backend::drawImage(FlxBackendImage *img, float x, float y, const FlxVector& scale, float angle,
                             const FlxRect& source, int color, bool flipped, float alpha)
{
    SFML_Image *gfx = (SFML_Image*)img;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    gfx->Graphic.Bind();

    glTranslatef(x + ((float)source.width / 2.f), y + ((float)source.height / 2.f), 0.f);
    glScalef(scale.x, scale.y, 0);
    glRotatef(FlxU::radToDegrees(angle), 0.f, 0.f, 1.f);
    glTranslatef((float)-source.width / 2.f, (float)-source.height / 2.f, 0.f);

    float vertices[] = {
        0.0f, 0.0f,
        (float)source.width, 0.0f,
        (float)source.width, (float)source.height,
        0.0f, (float)source.height
    };

    float texCoords[] = {
        source.x / gfx->getWidth(), source.y / gfx->getHeight(),
        (source.x + source.width) / gfx->getWidth(),  source.y / gfx->getHeight(),
        (source.x + source.width) / gfx->getWidth(), (source.y + source.height) / gfx->getHeight(),
        source.x / gfx->getWidth(), (source.y + source.height) / gfx->getHeight(),
    };

    if(flipped) {
        std::swap(texCoords[0], texCoords[2]);
        std::swap(texCoords[4], texCoords[6]);
    }

    unsigned char r = COLOR_GET_R(color);
    unsigned char g = COLOR_GET_G(color);
    unsigned char b = COLOR_GET_B(color);
    unsigned char a = static_cast<unsigned char>(alpha * 255.f);

    unsigned char colors[] = {
        r, g, b, a,
        r, g, b, a,
        r, g, b, a,
        r, g, b, a,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

FlxBaseText *SFML_Backend::createText(const wchar_t *text, void *font, int size, int color, float alpha) {
    if(!font) return NULL;

    FlxBaseText *data = new FlxBaseText();

    sf::String *str = new sf::String();
    str->SetFont(*((sf::Font*)font));
    str->SetText(text);
    str->SetSize((float)size);
    str->SetColor(sf::Color(COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color),
                            static_cast<unsigned char>(alpha * 255.f)));

    sf::FloatRect rect = str->GetRect();
    str->SetCenter(rect.GetWidth() / 2, rect.GetHeight() / 2);

    data->data = str;
    data->font = font;
    data->size = size;
    data->color = color;
    data->alpha = alpha;
    data->text = text;
    data->bounds.x = rect.GetWidth();
    data->bounds.y = rect.GetHeight();

    return data;
}

void SFML_Backend::destroyText(FlxBaseText *data) {

    if(data) {
        sf::String *str = (sf::String*)data->data;
        if(str) delete str;

        delete data;
    }
}

void SFML_Backend::drawText(FlxBaseText *text, float x, float y, const FlxVector& scale, float angle) {

    if(!text) return;
    if(!text->data) return;

    sf::String *str = (sf::String*) text->data;
    str->SetScale(scale.x, scale.y);
    str->SetRotation(-FlxU::radToDegrees(angle));
    str->SetPosition(x + (text->bounds.x / 2), y + (text->bounds.y / 2));

    window->Draw(*str);
}

FlxBackendImage* SFML_Backend::createImage(int width, int height, int color, float alpha) {
    SFML_Image *img = new SFML_Image();
    img->Graphic.Create(width, height, sf::Color(COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color),
                                                 static_cast<unsigned char>(alpha * 255.f)));
    img->Graphic.SetSmooth(false);

    return img;
}

FlxBackendImage *SFML_Backend::loadImage(const char *path) {

    if(images.find(path) != images.end()) {
        return images[path];
    }

    SFML_Image *img = new SFML_Image();
    if(!img->Graphic.LoadFromFile(path)) return false;

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

    // default charset
    static const wchar_t charset[] = L"abcdefghijklmnopqrstuvwxyz"
        L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        L"0123456789"
        L"!@#$%^&*()_-+=|\\<,>.?/:;\"\'{}~` "
        L"ąćęłńóśźżĄĆĘŁŃÓŚŹŻ" // polish extension
        L"ßÖÜÄäöü" // german extension
        L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"; // russian extension

    sf::Font *font = new sf::Font();
    if(!font->LoadFromFile(path, fontSize, charset)) return false;

    fonts[ss.str()] = font;
    return font;
}

bool SFML_Backend::isShadersSupported() {
    return sf::PostFX::CanUsePostFX();
}

FlxBackendShader* SFML_Backend::loadShader(const char *path) {
    SFML_Shader *shader = new SFML_Shader();

    // load shader data
    SFML_File file;
    if(!file.open(path, "r", true)) return NULL;

    file.seek(0, SEEK_END);
    unsigned int size = file.tell();
    file.seek(0, SEEK_SET);

    char *buffer = new char[size + 1];
    memset(buffer, 0, size + 1);

    file.read(buffer, size);
    file.close();

    std::string shaderData(buffer, buffer + size - 1);
    delete[] buffer;

    // create shaders
    shader->shaderProgram  = glCreateProgram();
    shader->vertexShader   = glCreateShader(GL_VERTEX_SHADER);
    shader->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // set shaders source
    static int vertexShaderSize = sizeof(DefaultVertexShader);
    const GLchar *vert = DefaultVertexShader;
    glShaderSource(shader->vertexShader, 1, &vert, &vertexShaderSize);

    const GLchar *fragmentShaderCode = shaderData.c_str();
    int framgentShaderSize = (int)shaderData.length();
    glShaderSource(shader->fragmentShader, 1, &fragmentShaderCode, &framgentShaderSize);

    // compile shaders
    glCompileShader(shader->vertexShader);
    glCompileShader(shader->fragmentShader);
    glAttachShader(shader->shaderProgram, shader->vertexShader);
    glAttachShader(shader->shaderProgram, shader->fragmentShader);
    glLinkProgram(shader->shaderProgram);

    int compiled = 0;
    glGetShaderiv(shader->fragmentShader, GL_COMPILE_STATUS, &compiled);
    if(!compiled) {
        int logLen = 0, saved = 0;
        glGetShaderiv(shader->fragmentShader, GL_INFO_LOG_LENGTH , &logLen);

        GLchar *log = new GLchar[logLen];
        glGetInfoLogARB(shader->fragmentShader, logLen, &saved, log);

        std::cerr << std::string(log, logLen) << std::endl;
        delete[] log;

        return NULL;
    }

    shaders.push_back(shader);
    return shader;
}

void SFML_Backend::drawShader(FlxBackendShader *s) {
    if(!s) return;

    // get current framebuffer
    glBindTexture(GL_TEXTURE_2D, framebuffer);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, FlxPowerOf2(FlxG::width), FlxPowerOf2(FlxG::height), 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    SFML_Shader *shader = (SFML_Shader*) s;
    glUseProgram(shader->shaderProgram);

    // bind all textures
    int i = 0;
    for(std::map<std::string, GLint>::iterator it = shader->textures.begin(); it != shader->textures.end();
        it++)
    {
        int location = glGetUniformLocation(shader->shaderProgram, it->first.c_str());
        glUniform1i(location, i);

        glActiveTexture((GLenum)(GL_TEXTURE0 + i));
        glEnable(GL_TEXTURE_2D);

        if(it->second != -1) {
            glBindTexture(GL_TEXTURE_2D, it->second);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, framebuffer);
        }

        i++;
    }

    float bottom = (float)FlxG::height / (float)FlxPowerOf2(FlxG::height);
    float right = (float)FlxG::width / (float)FlxPowerOf2(FlxG::width);

    // draw effect as fullscreen quad
    glBegin(GL_QUADS);
         glTexCoord2f(0.f, bottom);
         glVertex2f(0.f, 0.f);

         glTexCoord2f(right, bottom);
         glVertex2f((float)FlxG::width, 0.f);

         glTexCoord2f(right, 0.f);
         glVertex2f((float)FlxG::width, (float)FlxG::height);

         glTexCoord2f(0.f, 0.f);
         glVertex2f(0.f, (float)FlxG::height);
    glEnd();

    // unbind shader
    for(int j = i; j >= 0; j--) {
        glActiveTexture((GLenum)(GL_TEXTURE0 + j));
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }

    glActiveTexture(GL_TEXTURE0);
    glUseProgram(0);
}

void* SFML_Backend::loadSound(const char *path) {

    if(sounds.find(path) != sounds.end()) {
        return sounds[path];
    }

    sf::SoundBuffer *buffer = new sf::SoundBuffer();
    if(!buffer->LoadFromFile(path)) return NULL;

    sounds[path] = buffer;
    return buffer;
}

FlxBackendMusic* SFML_Backend::loadMusic(const char *path) {

    if(music.find(path) != music.end()) {
        return music[path];
    }

    SFML_Music *m = new SFML_Music();
    if(!m->Track.OpenFromFile(path)) return NULL;

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

// standard PC file I/O
FlxBackendFile* SFML_Backend::openFile(const char *path, const char *mode, bool internal) {
    SFML_File *file = new SFML_File();
    return file->open(path, mode, internal) ? file : NULL;
}


// HTTP support
bool SFML_Backend::sendHttpRequest(FlxHttpRequest *req, FlxHttpResponse& resp) {

    sf::Http http;
    http.SetHost(req->host, req->port);

    sf::Http::Request request;
    request.SetMethod(req->method == FLX_HTTP_GET ? sf::Http::Request::Get : sf::Http::Request::Post);
    request.SetURI(req->resource);
    request.SetBody(req->postData);
    request.SetHttpVersion(1, 0);

	// add content-lenght and content-type
	if(req->header.find("Content-Length") == req->header.end() && req->postData.length() != 0) {
		req->header["Content-Length"] = FlxU::toString((int)req->postData.length());
	}
	if(req->header.find("Content-Type") == req->header.end() && req->postData.length() != 0) {
		req->header["Content-Type"] = "application/octet-stream";
	}


    for(std::map<std::string, std::string>::iterator it = req->header.begin(); it != req->header.end(); it++) {
        request.SetField(it->first, it->second);
    }

    // wait for response
    sf::Http::Response response = http.SendRequest(request);

    resp.code = response.GetStatus();
    resp.data = response.GetBody();

    std::string val;
    if((val = response.GetField("Date")) != "") resp.header["Date"] = val;
    if((val = response.GetField("Set-Cookie")) != "") resp.header["Set-Cookie"] = val;
    if((val = response.GetField("Content-Type")) != "") resp.header["Content-Type"] = val;
    if((val = response.GetField("Content-Length")) != "") resp.header["Content-Length"] = val;
    if((val = response.GetField("Pragma")) != "") resp.header["Pragma"] = val;
    if((val = response.GetField("Transfer-Encoding")) != "") resp.header["Transfer-Encoding"] = val;
    if((val = response.GetField("Server")) != "") resp.header["Server"] = val;
    if((val = response.GetField("Cache-Control")) != "") resp.header["Cache-Control"] = val;
    if((val = response.GetField("Expires")) != "") resp.header["Expires"] = val;

    return (resp.code != 1001 && resp.code != 1000);
}
