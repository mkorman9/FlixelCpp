/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_INITIALIZER_LIST_H_
#define _FLX_INITIALIZER_LIST_H_

#include "cpp.h"

// initializer list class
// bypass for Visual Studio
template<typename T>
class FlxInitializerList {

public:
    std::list<T> arguments;

    FlxInitializerList(const std::initializer_list<T>& args) {
        for(auto it = args.begin(); it != args.end(); it++) {
            arguments.push_back(*it);
        }
    }

    FlxInitializerList(T t1) {
        arguments.push_back(t1);
    }

    FlxInitializerList(T t1, T t2) {
        arguments.push_back(t1);
        arguments.push_back(t2);
    }

    FlxInitializerList(T t1, T t2, T t3) {
        arguments.push_back(t1);
        arguments.push_back(t2);
        arguments.push_back(t3);
    }

    FlxInitializerList(T t1, T t2, T t3, T t4) {
        arguments.push_back(t1);
        arguments.push_back(t2);
        arguments.push_back(t3);
        arguments.push_back(t4);
    }

    FlxInitializerList(T t1, T t2, T t3, T t4, T t5) {
        arguments.push_back(t1);
        arguments.push_back(t2);
        arguments.push_back(t3);
        arguments.push_back(t4);
        arguments.push_back(t5);
    }

    FlxInitializerList(T t1, T t2, T t3, T t4, T t5, T t6) {
        arguments.push_back(t1);
        arguments.push_back(t2);
        arguments.push_back(t3);
        arguments.push_back(t4);
        arguments.push_back(t5);
        arguments.push_back(t6);
    }

    FlxInitializerList(T t1, T t2, T t3, T t4, T t5, T t6, T t7) {
        arguments.push_back(t1);
        arguments.push_back(t2);
        arguments.push_back(t3);
        arguments.push_back(t4);
        arguments.push_back(t5);
        arguments.push_back(t6);
        arguments.push_back(t7);
    }

    FlxInitializerList(T t1, T t2, T t3, T t4, T t5, T t6, T t7, T t8) {
        arguments.push_back(t1);
        arguments.push_back(t2);
        arguments.push_back(t3);
        arguments.push_back(t4);
        arguments.push_back(t5);
        arguments.push_back(t6);
        arguments.push_back(t7);
        arguments.push_back(t8);
    }

    FlxInitializerList(T t1, T t2, T t3, T t4, T t5, T t6, T t7, T t8, T t9) {
        arguments.push_back(t1);
        arguments.push_back(t2);
        arguments.push_back(t3);
        arguments.push_back(t4);
        arguments.push_back(t5);
        arguments.push_back(t6);
        arguments.push_back(t7);
        arguments.push_back(t8);
        arguments.push_back(t9);
    }

    FlxInitializerList(T t1, T t2, T t3, T t4, T t5, T t6, T t7, T t8, T t9, T t10) {
        arguments.push_back(t1);
        arguments.push_back(t2);
        arguments.push_back(t3);
        arguments.push_back(t4);
        arguments.push_back(t5);
        arguments.push_back(t6);
        arguments.push_back(t7);
        arguments.push_back(t8);
        arguments.push_back(t9);
        arguments.push_back(t10);
    }
};

#endif
