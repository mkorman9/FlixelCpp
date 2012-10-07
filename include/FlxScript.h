/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_SCRIPT_H_
#define _FLX_SCRIPT_H_

#ifndef FLX_NO_SCRIPT

#include "backend/cpp.h"
#include <angelscript.h>
#include <angelscript/scriptbuilder/scriptbuilder.h>

#define FLX_CONTEXT asIScriptContext

class FlxScriptEngine;

// Script object
class FlxScript {

private:
    FlxScriptEngine *engine;
    CScriptBuilder builder;
    asIScriptModule *mainModule;

    friend class FlxScriptEngine;
public:
    FlxScript(FlxScriptEngine *eng) { engine = eng; }

    inline CScriptBuilder& getBuilder() { return builder; }
    inline asIScriptModule* getModule() { return mainModule; }
    inline FlxScriptEngine* getEngine() { return engine; }

    // run function from script
    asIScriptContext *findFunction(const char *funcDecl);
    void endCall(asIScriptContext *ctx);
};


// Scripts managment class
class FlxScriptEngine {

private:
    asIScriptEngine *engine;
    void bindFlixelFunctionality();
public:

    // this functions are automatically called by Flixel
    void init();
    void finalize();

    // internals
    inline asIScriptEngine* getCore() { return engine; }

    // functions/variables registering
    void registerFunction(const char *decl, const asSFuncPtr& ptr, asDWORD conv = asCALL_CDECL);
    void registerProperty(const char *decl, void *ptr);
    void registerEnum(const char *name);
    void registerEnumValue(const char *enumName, const char *name, int value);
    void registerType(const char *name, int size, asDWORD flags = asOBJ_REF);
    void registerMethod(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                        asDWORD conv = asCALL_THISCALL);
    void registerClassProperty(const char *typeName, const char *decl, int offset);
    void registerClassConstructor(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);
    void registerClassDestructor(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);
    void registerClassAddref(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);
    void registerClassRelease(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);
    void registerClassFactory(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);
    void registerInterface(const char *name);
    void registerInterfaceMethod(const char *interface, const char *decl);

    // load script
    FlxScript* loadScript(const char *path);
};

#else

// dummies
class FlxScript {
};

class FlxScriptEngine {

public:
    void init() {}
    void finalize() {}
};

#endif


// Group of scripts (help class)
class FlxScriptsList {

public:
    std::vector<FlxScript*> members;

    FlxScript* add(FlxScript *s) {
        if(!s) return NULL;

        members.push_back(s);
        return s;
    }

    bool remove(FlxScript *s) {
        if(!s) return false;

        for(unsigned int i = 0; i < members.size(); i++) {
            if(members[i] == s) {
                members.erase(members.begin() + i);
                return true;
            }
        }

        return false;
    }

    void clear() {
        for(unsigned int i = 0; i < members.size(); i++) {
            if(members[i]) delete members[i];
        }

        members.clear();
    }
};

#endif

