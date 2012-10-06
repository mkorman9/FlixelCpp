#ifndef FLX_NO_SCRIPT

#include "FlxScript.h"
#include "FlxG.h"
#include <angelscript/scriptstdstring/scriptstdstring.h>
#include <angelscript/scriptany/scriptany.h>
#include <angelscript/scriptarray/scriptarray.h>
#include <angelscript/scriptdictionary/scriptdictionary.h>
#include <angelscript/scriptmath/scriptmath.h>

// default log callback
extern void FlxScriptMessageCallback(const asSMessageInfo *msg, void *param) {
    (void)param;

    std::string type = "ERROR: ";
	if(msg->type == asMSGTYPE_WARNING)
		type = "WARNING:";
	else if(msg->type == asMSGTYPE_INFORMATION)
		type = "INFO: ";

	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type.c_str(), msg->message);
}



/*
   Script members
*/
asIScriptContext *FlxScript::findFunction(const char *funcDecl) {
    asIScriptFunction *func = mainModule->GetFunctionByDecl(funcDecl);
    if(func == 0) return NULL;

    asIScriptContext *ctx = engine->getEngine()->CreateContext();
    ctx->Prepare(func);

    return ctx;
}


void FlxScript::endCall(asIScriptContext *ctx) {
    if(ctx) ctx->Release();
}


/*
   Script Engine members
*/
void FlxScriptEngine::init() {
    engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
    RegisterStdString(engine);
    RegisterScriptAny(engine);
    RegisterScriptArray(engine, true);
    RegisterScriptDictionary(engine);
    RegisterScriptMath(engine);

    engine->SetMessageCallback(asFUNCTION(FlxScriptMessageCallback), 0, asCALL_CDECL);
}


void FlxScriptEngine::finalize() {
    engine->Release();
}


FlxScript* FlxScriptEngine::loadScript(const char *path) {

    // read script from file
    FlxBackendFile *file = FlxG::backend->openFile(path, "r", true);
    if(!file) return NULL;

    file->seek(0, SEEK_END);
    unsigned int size = file->tell();
    file->seek(0, SEEK_SET);

    char *buffer = new char[size + 1];
	memset(buffer, 0, size + 1);

    file->read(buffer, size);
    delete file;


    // compile script
    FlxScript *script = new FlxScript(this);

    script->builder.StartNewModule(engine, path);
    script->builder.AddSectionFromMemory(buffer, path);
    if(script->builder.BuildModule() < 0) { delete script; return NULL; }

    script->mainModule = engine->GetModule(path);

	delete[] buffer;
    return script;
}


void FlxScriptEngine::registerFunction(const char *decl, const asSFuncPtr& ptr, asDWORD conv) {
    engine->RegisterGlobalFunction(decl, ptr, conv);
}


void FlxScriptEngine::registerProperty(const char *decl, void *ptr) {
    engine->RegisterGlobalProperty(decl, ptr);
}


void FlxScriptEngine::registerEnum(const char *name) {
    engine->RegisterEnum(name);
}


void FlxScriptEngine::registerEnumValue(const char *enumName, const char *name, int value) {
    engine->RegisterEnumValue(enumName, name, value);
}


void FlxScriptEngine::registerType(const char *name, int size, asDWORD flags) {
    engine->RegisterObjectType(name, size, flags);
}


void FlxScriptEngine::registerMethod(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                     asDWORD conv)
{
    engine->RegisterObjectMethod(typeName, decl, ptr, conv);
}


void FlxScriptEngine::registerClassProperty(const char *typeName, const char *decl, int offset) {
    engine->RegisterObjectProperty(typeName, decl, offset);
}


void FlxScriptEngine::registerClassConstructor(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                               asDWORD conv)
{
    engine->RegisterObjectBehaviour(typeName, asBEHAVE_CONSTRUCT, decl, ptr, conv);
}


void FlxScriptEngine::registerClassDestructor(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                               asDWORD conv)
{
    engine->RegisterObjectBehaviour(typeName, asBEHAVE_DESTRUCT, decl, ptr, conv);
}


#endif
