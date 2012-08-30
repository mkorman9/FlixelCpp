#include "FlxSave.h"
#include "FlxU.h"
#include "backend/BackendHolder.h"

void FlxSave::set(const char *name, const char *Data) {
    data[name] = Data;
}


void FlxSave::set(const char *name, int Data) {
    data[name] = FlxU::toString(Data);
}


void FlxSave::set(const char *name, float Data) {
    data[name] = FlxU::toString(Data);
}


std::string FlxSave::getString(const char *name) {
    return data[name];
}


int FlxSave::getNumber(const char *name) {
    return FlxU::toNumber(data[name]);
}


float FlxSave::getFloatNumber(const char *name) {
    return FlxU::toFloatNumber(data[name]);
}


void FlxSave::save(const char *path) {
    BackendHolder::get().getBackend()->saveData(path, data);
}


bool FlxSave::load(const char *path) {
    return BackendHolder::get().getBackend()->loadData(path, data);
}

