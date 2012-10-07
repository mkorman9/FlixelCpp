#include "FlxSave.h"
#include "FlxU.h"
#include "FlxG.h"

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
    FlxBackendFile *file = FlxG::backend->openFile(path, "wb", false);
    if(!file) return;

    std::string rawData;
    for(auto it = data.begin(); it != data.end(); it++) {
        rawData += it->first + '\n' + it->second + '\n';
    }

    // encode data to prevent manual save changes
    // note: this is not an encryption!
    for(unsigned int i = 0; i < rawData.size(); i++) {
        rawData[i] ^= 24;
    }

    file->write(rawData.data(), rawData.size());
	
    delete file;
}


bool FlxSave::load(const char *path) {
    FlxBackendFile *file = FlxG::backend->openFile(path, "rb", false);
    if(!file) return false;

    file->seek(0, SEEK_END);
    unsigned int size = file->tell();
    file->seek(0, SEEK_SET);

    char *buffer = new char[size + 1];
	memset(buffer, 0, size + 1);

    file->read(buffer, size);

    for(unsigned int i = 0; i < size; i++) {
        buffer[i] ^= 24;
    }

    std::string rawData(buffer, buffer + size - 1);

    delete[] buffer;
    delete file;

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

