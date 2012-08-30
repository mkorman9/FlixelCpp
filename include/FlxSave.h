/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_SAVE_H_
#define _FLX_SAVE_H_

#include "backend/cpp.h"

/*
*  Save file class
*/
class FlxSave {

private:
    std::map<std::string, std::string> data;
public:

    // add text data line
    void set(const char *name, const char *data);

    // add number data line
    void set(const char *name, int data);

    // add number (float) data line
    void set(const char *name, float data);

    // get data line as text
    std::string getString(const char *name);

    // get data line as number
    int getNumber(const char *name);

    // get data line as number (float)
    float getFloatNumber(const char *name);

    // save data to file
    void save(const char *path);

    // load data from file
    bool load(const char *path);
};

#endif




