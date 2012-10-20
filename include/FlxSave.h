/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_SAVE_H_
#define _FLX_SAVE_H_

#include "backend/cpp.h"

/**
*  Save file
*/
class FlxSave {

private:
    std::map<std::string, std::string> data;
public:

    /**
	*  Set variable's value to some string data
	*  @param name Variable's name
	*  @param data Value
	*/
    void set(const char *name, const char *data);

    /**
	*  Set variable's value to some int data
	*  @param name Variable's name
	*  @param data Value
	*/
    void set(const char *name, int data);

    /**
	*  Set variable's value to some float data
	*  @param name Variable's name
	*  @param data Value
	*/
    void set(const char *name, float data);

    /**
	*  Get variables value and convert it to string format
	*  @param name Variable's name
	*  @return Value in string format
	*/
    std::string getString(const char *name);

    /**
	*  Get variables value and convert it to int format
	*  @param name Variable's name
	*  @return Value in int format
	*/
    int getNumber(const char *name);

    /**
	*  Get variables value and convert it to float format
	*  @param name Variable's name
	*  @return Value in float format
	*/
    float getFloatNumber(const char *name);

    /**
	*  Save specified values to file
	*  @param path Path to output file (in external device's storage)
	*/
    void save(const char *path);

    /**
	*  Load variables from file
	*  @param path Path to input file (in external device's storage)
	*  @return Loading result
	*/
    bool load(const char *path);
};

#endif

