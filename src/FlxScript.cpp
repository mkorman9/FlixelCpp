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

    asIScriptContext *ctx = engine->getCore()->CreateContext();
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

    bindFlixelFunctionality();

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


void FlxScriptEngine::registerClassAddref(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                          asDWORD conv)
{
    engine->RegisterObjectBehaviour(typeName, asBEHAVE_ADDREF, decl, ptr, conv);
}


void FlxScriptEngine::registerClassRelease(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                                           asDWORD conv)
{
    engine->RegisterObjectBehaviour(typeName, asBEHAVE_RELEASE, decl, ptr, conv);
}


void FlxScriptEngine::registerClassFactory(const char *typeName, const char *decl, const asSFuncPtr& ptr,
                        asDWORD conv)
{
    engine->RegisterObjectBehaviour(typeName, asBEHAVE_FACTORY, decl, ptr, conv);
}


void FlxScriptEngine::registerInterface(const char *name) {
    engine->RegisterInterface(name);
}


void FlxScriptEngine::registerInterfaceMethod(const char *interface, const char *decl) {
    engine->RegisterInterfaceMethod(interface, decl);
}


/*
   Flixel functionality
*/
static bool isKeyDown(FlxKey::KeyCode key) {
    return FlxG::key->down(key);
}


static bool isKeyPressed(FlxKey::KeyCode key) {
    return FlxG::key->pressed(key);
}


static bool isKeyReleased(FlxKey::KeyCode key) {
    return FlxG::key->released(key);
}


static int getTouchesCount() {
    return FlxG::mouse.touchesCount();
}


static void FlxRect_addRef(asIScriptGeneric *gen) {
    FlxRect *self = (FlxRect*)gen->GetObject();
    self->_refCount++;
}


static void FlxRect_lostRef(asIScriptGeneric *gen) {
    FlxRect *self = (FlxRect*)gen->GetObject();
    if(--self->_refCount != 0) delete self;
}


static void FlxRect_create(asIScriptGeneric *gen) {
    *(FlxRect**)gen->GetAddressOfReturnLocation() = new FlxRect();
}


static void FlxRect_createParams(asIScriptGeneric *gen) {
    float x = gen->GetArgFloat(0);
    float y = gen->GetArgFloat(1);
    int width = gen->GetArgDWord(2);
    int height = gen->GetArgDWord(3);

    *(FlxRect**)gen->GetAddressOfReturnLocation() = new FlxRect(x, y, width, height);
}


static void FlxRect_copy(asIScriptGeneric *gen) {
    FlxRect *self = (FlxRect*)gen->GetObject();
    FlxRect *other = *(FlxRect**)gen->GetAddressOfArg(0);
	*self = *other;
	*(FlxRect**)gen->GetAddressOfReturnLocation() = self;
}


static void FlxVector_addRef(asIScriptGeneric *gen) {
    FlxVector *self = (FlxVector*)gen->GetObject();
    self->_refCount++;
}


static void FlxVector_lostRef(asIScriptGeneric *gen) {
    FlxVector *self = (FlxVector*)gen->GetObject();
    if(--self->_refCount != 0) delete self;
}


static void FlxVector_create(asIScriptGeneric *gen) {
    *(FlxVector**)gen->GetAddressOfReturnLocation() = new FlxVector();
}


static void FlxVector_createParams2(asIScriptGeneric *gen) {
    float x = gen->GetArgFloat(0);
    float y = gen->GetArgFloat(1);

    *(FlxVector**)gen->GetAddressOfReturnLocation() = new FlxVector(x, y);
}

static void FlxVector_createParams4(asIScriptGeneric *gen) {
    float x1 = gen->GetArgFloat(0);
    float y1 = gen->GetArgFloat(1);
    float x2 = gen->GetArgFloat(2);
    float y2 = gen->GetArgFloat(3);

    *(FlxVector**)gen->GetAddressOfReturnLocation() = new FlxVector(x1, y1, x2, y2);
}


static void FlxVector_createParams2vec(asIScriptGeneric *gen) {
    FlxVector *one = *(FlxVector**)gen->GetAddressOfArg(0);
    FlxVector *two = *(FlxVector**)gen->GetAddressOfArg(1);

    *(FlxVector**)gen->GetAddressOfReturnLocation() = new FlxVector(*one, *two);
}


static void FlxVector_copy(asIScriptGeneric *gen) {
    FlxVector *self = (FlxVector*)gen->GetObject();
    FlxVector *other = *(FlxVector**)gen->GetAddressOfArg(0);
	*self = *other;
	*(FlxVector**)gen->GetAddressOfReturnLocation() = self;
}


static void playSound(const std::string& path, float volume) {
    FlxG::play(path.c_str(), volume);
}


static void playMusic(const std::string& path, float volume) {
    FlxG::playMusic(path.c_str(), volume);
}


static void stopMusic() {
    if(FlxG::music && FlxG::music->isPlaying()) FlxG::music->stop();
}


static bool isTouchDown(int idx) {
    return FlxG::mouse.down(idx) != NULL;
}


static bool isTouchPressed(int idx) {
    return FlxG::mouse.pressed(idx) != NULL;
}


static bool isTouchReleased(int idx) {
    return FlxG::mouse.released(idx) != NULL;
}


static bool isTouchDownOnArea(const FlxRect& rect, int idx) {
    return FlxG::mouse.downOnArea(rect, idx) != NULL;
}


static bool isTouchPressedOnArea(const FlxRect& rect, int idx) {
    return FlxG::mouse.pressedOnArea(rect, idx) != NULL;
}


static bool isTouchReleasedOnArea(const FlxRect& rect, int idx) {
    return FlxG::mouse.releasedOnArea(rect, idx) != NULL;
}


static bool isMiddleDown() {
    return FlxG::mouse.middleDown() != 0;
}


static bool isMiddlePressed() {
    return FlxG::mouse.middlePressed() != 0;
}


static bool isMiddleReleased() {
    return FlxG::mouse.middleReleased() != 0;
}


static bool isRightDown() {
    return FlxG::mouse.rightDown() != 0;
}


static bool isRightPressed() {
    return FlxG::mouse.rightPressed() != 0;
}


static bool isRightReleased() {
    return FlxG::mouse.rightReleased() != 0;
}


static void FlxObject_addRef(asIScriptGeneric *gen) {
    (void)gen; // don't delete FlxObject
}


static void FlxObject_lostRef(asIScriptGeneric *gen) {
    (void)gen; // don't delete FlxObject
}


static unsigned int getObjectsCount() {
    if(FlxG::state) return FlxG::state->members.size();
    return 0;
}


static bool isObject(unsigned int idx) {
    if(FlxG::state) {
        if(idx >= FlxG::state->members.size()) return false;
        return FlxG::state->members[idx]->entityType == FLX_OBJECT;
    }

    return false;
}


static FlxObject* getObject(unsigned int idx) {
    if(FlxG::state) {
        return (FlxObject*) FlxG::state->members[idx];
    }

    return 0;
}


void FlxScriptEngine::bindFlixelFunctionality() {

    // bind keycodes
    registerEnum("FlxKey");
    registerEnumValue("FlxKey", "A", FlxKey::A);
    registerEnumValue("FlxKey", "B", FlxKey::B);
    registerEnumValue("FlxKey", "C", FlxKey::C);
    registerEnumValue("FlxKey", "D", FlxKey::D);
    registerEnumValue("FlxKey", "E", FlxKey::E);
    registerEnumValue("FlxKey", "F", FlxKey::G);
    registerEnumValue("FlxKey", "G", FlxKey::H);
    registerEnumValue("FlxKey", "H", FlxKey::H);
    registerEnumValue("FlxKey", "I", FlxKey::I);
    registerEnumValue("FlxKey", "J", FlxKey::J);
    registerEnumValue("FlxKey", "K", FlxKey::K);
    registerEnumValue("FlxKey", "L", FlxKey::L);
    registerEnumValue("FlxKey", "M", FlxKey::M);
    registerEnumValue("FlxKey", "N", FlxKey::N);
    registerEnumValue("FlxKey", "O", FlxKey::O);
    registerEnumValue("FlxKey", "P", FlxKey::P);
    registerEnumValue("FlxKey", "Q", FlxKey::Q);
    registerEnumValue("FlxKey", "R", FlxKey::R);
    registerEnumValue("FlxKey", "S", FlxKey::S);
    registerEnumValue("FlxKey", "T", FlxKey::T);
    registerEnumValue("FlxKey", "U", FlxKey::U);
    registerEnumValue("FlxKey", "V", FlxKey::V);
    registerEnumValue("FlxKey", "W", FlxKey::W);
    registerEnumValue("FlxKey", "X", FlxKey::X);
    registerEnumValue("FlxKey", "Y", FlxKey::Y);
    registerEnumValue("FlxKey", "Z", FlxKey::Z);
    registerEnumValue("FlxKey", "Num0", FlxKey::Num0);
    registerEnumValue("FlxKey", "Num1", FlxKey::Num1);
    registerEnumValue("FlxKey", "Num2", FlxKey::Num2);
    registerEnumValue("FlxKey", "Num3", FlxKey::Num3);
    registerEnumValue("FlxKey", "Num4", FlxKey::Num4);
    registerEnumValue("FlxKey", "Num5", FlxKey::Num5);
    registerEnumValue("FlxKey", "Num6", FlxKey::Num6);
    registerEnumValue("FlxKey", "Num7", FlxKey::Num7);
    registerEnumValue("FlxKey", "Num8", FlxKey::Num8);
    registerEnumValue("FlxKey", "Num9", FlxKey::Num9);
    registerEnumValue("FlxKey", "Escape", FlxKey::Escape);
    registerEnumValue("FlxKey", "LControl", FlxKey::LControl);
    registerEnumValue("FlxKey", "LShift", FlxKey::LShift);
    registerEnumValue("FlxKey", "LAlt", FlxKey::LAlt);
    registerEnumValue("FlxKey", "LSystem", FlxKey::LSystem);
    registerEnumValue("FlxKey", "RControl", FlxKey::RControl);
    registerEnumValue("FlxKey", "RAlt", FlxKey::RAlt);
    registerEnumValue("FlxKey", "RShift", FlxKey::RShift);
    registerEnumValue("FlxKey", "RSystem", FlxKey::RSystem);
    registerEnumValue("FlxKey", "Menu", FlxKey::Menu);
    registerEnumValue("FlxKey", "LBracket", FlxKey::LBracket);
    registerEnumValue("FlxKey", "RBracket", FlxKey::RBracket);
    registerEnumValue("FlxKey", "SemiColon", FlxKey::SemiColon);
    registerEnumValue("FlxKey", "Comma", FlxKey::Comma);
    registerEnumValue("FlxKey", "Period", FlxKey::Period);
    registerEnumValue("FlxKey", "Quote", FlxKey::Quote);
    registerEnumValue("FlxKey", "Slash", FlxKey::Slash);
    registerEnumValue("FlxKey", "BackSlash", FlxKey::BackSlash);
    registerEnumValue("FlxKey", "Tilde", FlxKey::Tilde);
    registerEnumValue("FlxKey", "Equal", FlxKey::Equal);
    registerEnumValue("FlxKey", "Dash", FlxKey::Dash);
    registerEnumValue("FlxKey", "Space", FlxKey::Space);
    registerEnumValue("FlxKey", "Enter", FlxKey::Enter);
    registerEnumValue("FlxKey", "Back", FlxKey::Back);
    registerEnumValue("FlxKey", "Tab", FlxKey::Tab);
    registerEnumValue("FlxKey", "PageUp", FlxKey::PageUp);
    registerEnumValue("FlxKey", "PageDown", FlxKey::PageDown);
    registerEnumValue("FlxKey", "End", FlxKey::End);
    registerEnumValue("FlxKey", "Home", FlxKey::Home);
    registerEnumValue("FlxKey", "Insert", FlxKey::Insert);
    registerEnumValue("FlxKey", "Delete", FlxKey::Delete);
    registerEnumValue("FlxKey", "Add", FlxKey::Add);
    registerEnumValue("FlxKey", "Subtract", FlxKey::Subtract);
    registerEnumValue("FlxKey", "Multiply", FlxKey::Multiply);
    registerEnumValue("FlxKey", "Divide", FlxKey::Divide);
    registerEnumValue("FlxKey", "Left", FlxKey::Left);
    registerEnumValue("FlxKey", "Right", FlxKey::Right);
    registerEnumValue("FlxKey", "Up", FlxKey::Up);
    registerEnumValue("FlxKey", "Down", FlxKey::Down);
    registerEnumValue("FlxKey", "Numpad0", FlxKey::Numpad0);
    registerEnumValue("FlxKey", "Numpad1", FlxKey::Numpad1);
    registerEnumValue("FlxKey", "Numpad2", FlxKey::Numpad2);
    registerEnumValue("FlxKey", "Numpad3", FlxKey::Numpad3);
    registerEnumValue("FlxKey", "Numpad4", FlxKey::Numpad4);
    registerEnumValue("FlxKey", "Numpad5", FlxKey::Numpad5);
    registerEnumValue("FlxKey", "Numpad6", FlxKey::Numpad6);
    registerEnumValue("FlxKey", "Numpad7", FlxKey::Numpad7);
    registerEnumValue("FlxKey", "Numpad8", FlxKey::Numpad8);
    registerEnumValue("FlxKey", "Numpad9", FlxKey::Numpad9);
    registerEnumValue("FlxKey", "F1", FlxKey::F1);
    registerEnumValue("FlxKey", "F2", FlxKey::F2);
    registerEnumValue("FlxKey", "F3", FlxKey::F3);
    registerEnumValue("FlxKey", "F4", FlxKey::F4);
    registerEnumValue("FlxKey", "F5", FlxKey::F5);
    registerEnumValue("FlxKey", "F6", FlxKey::F6);
    registerEnumValue("FlxKey", "F7", FlxKey::F7);
    registerEnumValue("FlxKey", "F8", FlxKey::F8);
    registerEnumValue("FlxKey", "F9", FlxKey::F9);
    registerEnumValue("FlxKey", "F10", FlxKey::F10);
    registerEnumValue("FlxKey", "F11", FlxKey::F11);
    registerEnumValue("FlxKey", "F12", FlxKey::F12);
    registerEnumValue("FlxKey", "F13", FlxKey::F13);
    registerEnumValue("FlxKey", "F14", FlxKey::F14);
    registerEnumValue("FlxKey", "F15", FlxKey::F15);
    registerEnumValue("FlxKey", "Pause", FlxKey::Pause);

    // register basic types
    registerType("FlxRect", sizeof(FlxRect), asOBJ_REF);
    registerClassAddref("FlxRect", "void f()", asFUNCTION(FlxRect_addRef), asCALL_GENERIC);
    registerClassRelease("FlxRect", "void f()", asFUNCTION(FlxRect_lostRef), asCALL_GENERIC);
    registerClassFactory("FlxRect", "FlxRect@ f()", asFUNCTION(FlxRect_create), asCALL_GENERIC);
    registerClassFactory("FlxRect", "FlxRect@ f(float,float,int,int)", asFUNCTION(FlxRect_createParams),
                         asCALL_GENERIC);
    registerClassProperty("FlxRect", "float x", asOFFSET(FlxRect, x));
    registerClassProperty("FlxRect", "float y", asOFFSET(FlxRect, y));
    registerClassProperty("FlxRect", "int width", asOFFSET(FlxRect, width));
    registerClassProperty("FlxRect", "int height", asOFFSET(FlxRect, height));
    registerMethod("FlxRect", "bool overlaps(const FlxRect&)", asMETHOD(FlxRect, overlaps));
    registerMethod("FlxRect", "FlxRect& opAssign(const FlxRect&)", asFUNCTION(FlxRect_copy), asCALL_GENERIC);

    registerType("FlxVector", sizeof(FlxVector), asOBJ_REF);
    registerClassAddref("FlxVector", "void f()", asFUNCTION(FlxVector_addRef), asCALL_GENERIC);
    registerClassRelease("FlxVector", "void f()", asFUNCTION(FlxVector_lostRef), asCALL_GENERIC);
    registerClassFactory("FlxVector", "FlxVector@ f()", asFUNCTION(FlxVector_create), asCALL_GENERIC);
    registerClassFactory("FlxVector", "FlxVector@ f(float,float)", asFUNCTION(FlxVector_createParams2),
                         asCALL_GENERIC);
    registerClassFactory("FlxVector", "FlxVector@ f(float,float,float,float)",
                         asFUNCTION(FlxVector_createParams4), asCALL_GENERIC);
    registerClassFactory("FlxVector", "FlxVector@ f(const FlxVector&, const FlxVector&)",
                         asFUNCTION(FlxVector_createParams2vec), asCALL_GENERIC);
    registerClassProperty("FlxVector", "float x", asOFFSET(FlxVector, x));
    registerClassProperty("FlxVector", "float y", asOFFSET(FlxVector, y));
    registerMethod("FlxVector", "FlxVector& opAssign(const FlxVector&)",
                   asFUNCTION(FlxVector_copy), asCALL_GENERIC);

    // sound/music
    registerFunction("void playSound(string, float)", asFUNCTION(playSound));
    registerFunction("void playMusic(string, float)", asFUNCTION(playMusic));
    registerFunction("void stopMusic()", asFUNCTION(stopMusic));

    // input
    registerFunction("bool isKeyDown(FlxKey)", asFUNCTION(isKeyDown));
    registerFunction("bool isKeyPressed(FlxKey)", asFUNCTION(isKeyPressed));
    registerFunction("bool isKeyReleased(FlxKey)", asFUNCTION(isKeyReleased));
    registerFunction("int getTouchesCount()", asFUNCTION(getTouchesCount));
    registerFunction("bool isTouchDown(int idx = -1)", asFUNCTION(isTouchDown));
    registerFunction("bool isTouchPressed(int idx = -1)", asFUNCTION(isTouchPressed));
    registerFunction("bool isTouchReleased(int idx = -1)", asFUNCTION(isTouchReleased));
    registerFunction("bool isTouchDownOnArea(const FlxRect& area, int idx)",
                     asFUNCTION(isTouchDownOnArea));
    registerFunction("bool isTouchPressedOnArea(const FlxRect& area, int idx = -1)",
                     asFUNCTION(isTouchPressedOnArea));
    registerFunction("bool isTouchReleasedOnArea(const FlxRect& area, int idx = -1)",
                     asFUNCTION(isTouchReleasedOnArea));
    registerFunction("bool isMiddleDown(int idx = -1)", asFUNCTION(isMiddleDown));
    registerFunction("bool isMiddlePressed(int idx = -1)", asFUNCTION(isMiddlePressed));
    registerFunction("bool isMiddleReleased(int idx = -1)", asFUNCTION(isMiddleReleased));
    registerFunction("bool isRightDown(int idx = -1)", asFUNCTION(isRightDown));
    registerFunction("bool isRightPressed(int idx = -1)", asFUNCTION(isRightPressed));
    registerFunction("bool isRightReleased(int idx = -1)", asFUNCTION(isRightReleased));

    // object managment interface
    registerType("FlxObject", sizeof(FlxObject), asOBJ_REF);
    registerClassAddref("FlxObject", "void f()", asFUNCTION(FlxObject_addRef), asCALL_GENERIC);
    registerClassRelease("FlxObject", "void f()", asFUNCTION(FlxObject_lostRef), asCALL_GENERIC);
    registerClassProperty("FlxObject", "float x", asOFFSET(FlxObject, x));
    registerClassProperty("FlxObject", "float y", asOFFSET(FlxObject, y));
    registerClassProperty("FlxObject", "int width", asOFFSET(FlxObject, width));
    registerClassProperty("FlxObject", "int height", asOFFSET(FlxObject, height));
    registerClassProperty("FlxObject", "bool active", asOFFSET(FlxObject, active));
    registerClassProperty("FlxObject", "bool visible", asOFFSET(FlxObject, visible));
    registerClassProperty("FlxObject", "FlxVector velocity", asOFFSET(FlxObject, velocity));
    registerClassProperty("FlxObject", "FlxVector acceleration", asOFFSET(FlxObject, acceleration));
    registerClassProperty("FlxObject", "FlxVector maxVelocity", asOFFSET(FlxObject, maxVelocity));
    registerClassProperty("FlxObject", "float angularVelocity", asOFFSET(FlxObject, angularVelocity));
    registerClassProperty("FlxObject", "float angle", asOFFSET(FlxObject, angle));
    registerClassProperty("FlxObject", "float scale", asOFFSET(FlxObject, scale));
    registerClassProperty("FlxObject", "int color", asOFFSET(FlxObject, color));
    registerClassProperty("FlxObject", "FlxRect hitbox", asOFFSET(FlxObject, hitbox));
    registerClassProperty("FlxObject", "FlxVector hitboxMove", asOFFSET(FlxObject, hitboxMove));
    registerClassProperty("FlxObject", "bool collisions", asOFFSET(FlxObject, collisions));
    registerClassProperty("FlxObject", "float alpha", asOFFSET(FlxObject, alpha));
    registerClassProperty("FlxObject", "bool isGUI", asOFFSET(FlxObject, isGUI));
    registerClassProperty("FlxObject", "bool isFollowingPath", asOFFSET(FlxObject, isFollowingPath));
    registerClassProperty("FlxObject", "float followingVelocity", asOFFSET(FlxObject, followingVelocity));
    registerMethod("FlxObject", "FlxVector@ getCenter()", asMETHOD(FlxObject, getCenter));
    registerMethod("FlxObject", "void kill()", asMETHOD(FlxObject, kill));

    registerFunction("uint getObjectsCount()", asFUNCTION(getObjectsCount));
    registerFunction("bool isObject(uint index)", asFUNCTION(isObject));
    registerFunction("FlxObject@ getObject(uint index)", asFUNCTION(getObject));
}

#endif
