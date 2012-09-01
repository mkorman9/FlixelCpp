#include "FlxShader.h"
#include "backend/BackendHolder.h"

FlxShader::FlxShader(const char *fragmentShaderFile) {

    if(!BackendHolder::get().getBackend()->isShadersSupported()) {
        std::cerr << "[Error] Shaders aren't supported on this platform" << std::endl;
        data = NULL;
        return;
    }

    data = BackendHolder::get().getBackend()->loadShader(fragmentShaderFile);
}


void FlxShader::setParameter(const char *name, float x) {
    if(!data) return;
    data->setParameter(name, x);
}


void FlxShader::setParameter(const char *name, float x, float y) {
    if(!data) return;
    data->setParameter(name, x, y);
}


void FlxShader::setParameter(const char *name, const FlxVector& vec) {
    if(!data) return;
    data->setParameter(name, vec.x, vec.y);
}


void FlxShader::setParameter(const char *name, float x, float y, float z) {
    if(!data) return;
    data->setParameter(name, x, y, z);
}


void FlxShader::setParameter(const char *name, float x, float y, float z, float w) {
    if(!data) return;
    data->setParameter(name, x, y, z, w);
}

void FlxShader::setParameter(const char *name, int rgb) {
    if(!data) return;
    data->setParameter(name, (float)COLOR_GET_R(rgb) / 255.f, (float)COLOR_GET_G(rgb) / 255.f,
                    (float)COLOR_GET_B(rgb) / 255.f);
}

void FlxShader::setParameter(const char *name, int rgb, float alpha) {
    if(!data) return;
    data->setParameter(name, (float)COLOR_GET_R(rgb) / 255.f, (float)COLOR_GET_G(rgb) / 255.f,
                    (float)COLOR_GET_B(rgb) / 255.f, alpha);
}


void FlxShader::setTexture(const char *name, const char *texFile) {
    if(!data) return;

    if(!texFile) {
        data->setParameter(name, (FlxBackendImage*) NULL);
    }
    else {
        FlxBackendImage *img = BackendHolder::get().getBackend()->loadImage(texFile);
        data->setParameter(name, img);
    }
}
