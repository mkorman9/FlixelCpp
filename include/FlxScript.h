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

/**
*  Single script object
*/
class FlxScript {

private:
    FlxScriptEngine *engine;
    CScriptBuilder builder;
    asIScriptModule *mainModule;

    friend class FlxScriptEngine;
public:

	/**
	*  Default constructor
	*  @param eng Pointer to script engine
	*/
    FlxScript(FlxScriptEngine *eng) { engine = eng; }
	
	/**
	*  Get AngelScript script builder
	*  @return AngelScript script builder
	*/
    inline CScriptBuilder& getBuilder() { return builder; }
	
	/**
	*  Get script main module
	*  @return Script main module
	*/
    inline asIScriptModule* getModule() { return mainModule; }
	
	/**
	*  Get script engine
	*  @return Script engine
	*/
    inline FlxScriptEngine* getEngine() { return engine; }

	/**
	*  Find function in script's main module.
	*  @param funcDecl Function's declaration
	*  @return Function context or <code>NULL</code> on failure
	*/
    FLX_CONTEXT *findFunction(const char *funcDecl);
	
	/**
	*  End function calling and delete function context.
	*  @param ctx Function's context
	*/
    void endCall(FLX_CONTEXT *ctx);
};


/**
*  Scripts managment class.<br />
*  Scripting documentation is not ready yet
*/
class FlxScriptEngine {

private:
    asIScriptEngine *engine;
    void bindFlixelFunctionality();
public:

    /**
	*  Initialize engine (Internal! Do not touch!)
	*/
    void init();
	
	/**
	*  Close engine (Internal! Do not touch!)
	*/
    void finalize();

    /**
	*  Get AngelScript core device
	*  @return Pointer to AngelScript engine
	*/
    inline asIScriptEngine* getCore() { return engine; }

    /**
	*  Register global function
	*  @param decl Declaration of function
	*  @param ptr Pointer to function
	*  @param conv Calling convention
	*/
    void registerFunction(const char *decl, const asSFuncPtr& ptr, asDWORD conv = asCALL_CDECL);
	
	/**
	*  Register global property
	*  @param decl Declaration of property
	*  @param ptr Pointer to memory
	*/
    void registerProperty(const char *decl, void *ptr);
	
	/**
	*  Register new enum
	*  @param name Enum name
	*/
    void registerEnum(const char *name);
	
	/**
	*  Register new enum variable
	*  @param enumName Enum name
	*  @param name Variable name
	*  @param value Value
	*/
    void registerEnumValue(const char *enumName, const char *name, int value);
	
	/**
	*  Register new class
	*  @param name Class name
	*  @param size Size of class (in bytes)
	*  @param flags Special flags
	*/
    void registerType(const char *name, int size, asDWORD flags = asOBJ_REF);
	
	/**
	*  Register class method
	*  @param typeName Class name
	*  @param decl Method declaration
	*  @param ptr Pointer to method
	*  @param conv Calling convention
	*/
    void registerMethod(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                        asDWORD conv = asCALL_THISCALL);
						
	/**
	*  Register new class property
	*  @param typeName Class name
	*  @param decl Declaration of property
	*  @param offset Offset in class
	*/
    void registerClassProperty(const char *typeName, const char *decl, int offset);
	
	/**
	*  Register new class constructor
	*  @param typeName Class name
	*  @param decl Declaration of constructor
	*  @param ptr Pointer to function
	*  @param conv Convention of calling
	*/
    void registerClassConstructor(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);
								  
	/**
	*  Register new class destructor
	*  @param typeName Class name
	*  @param decl Declaration of destructor
	*  @param ptr Pointer to function
	*  @param conv Convention of calling
	*/
    void registerClassDestructor(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);
								  
	/**
	*  Register new class AddReference event
	*  @param typeName Class function
	*  @param decl Declaration of function
	*  @param ptr Pointer to function
	*  @param conv Convention of calling
	*/
    void registerClassAddref(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);
								 
	/**
	*  Register new class RemoveReference event
	*  @param typeName Class function
	*  @param decl Declaration of function
	*  @param ptr Pointer to function
	*  @param conv Convention of calling
	*/
    void registerClassRelease(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);

	/**
	*  Register new class factory
	*  @param typeName Class function
	*  @param decl Declaration of function
	*  @param ptr Pointer to function
	*  @param conv Convention of calling
	*/
    void registerClassFactory(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                  asDWORD conv = asCALL_THISCALL);
								  
	/**
	*  Register new interface
	*  @param name Interface name
	*/
    void registerInterface(const char *name);
	
	/**
	*  Register new interface method
	*  @param interface Interface name
	*  @param decl Declaration of method
	*/
    void registerInterfaceMethod(const char *interface, const char *decl);

	/**
	*  Load and script
	*  @param path Path to script file (in local device's stoarage)
	*  @return Pointer to new script object or <code>NULL</code>
	*/
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


/**
*  Group of scripts (help class for FlxG)
*/
class FlxScriptsList {

public:	

	/**
	*  Collection of scripts
	*/
    std::vector<FlxScript*> members;

    /**
	*  Add new script to group
	*  @param s Script to add
	*  @return Pointer to <code>s</code>, for chaining
	*/
    FlxScript* add(FlxScript *s) {
        if(!s) return NULL;

        members.push_back(s);
        return s;
    }
	
    /**
	*  Remove scripts from group
	*  @param s Script to remove
	*  @return <code>true</code> if removement was successful. <code>false</code> if script was not found in group
	*/
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
	
    /**
	*  Remove all scripts from group
	*/
    void clear() {
        for(unsigned int i = 0; i < members.size(); i++) {
            if(members[i]) delete members[i];
        }

        members.clear();
    }
};

#endif

