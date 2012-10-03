LOCAL_PATH := $(call my-dir)/src

include $(CLEAR_VARS)

LOCAL_MODULE := flixel

LOCAL_C_INCLUDES := jni/flixel/include \
	jni/SDL/include \
	jni/SDL_image \
	jni/SDL_ttf \
	jni/SDL_net \
	jni/SDL_mixer

LOCAL_SRC_FILES := FlxButton.cpp \
	FlxEmitter.cpp \
	FlxG.cpp \
	FlxGroup.cpp \
	FlxKeyboard.cpp \
	FlxMouse.cpp \
	FlxMusic.cpp \
	FlxObject.cpp \
	FlxPreloader.cpp \
	FlxSave.cpp \
	FlxSound.cpp \
	FlxSprite.cpp \
	FlxText.cpp \
	FlxTilemap.cpp \
	FlxHttpRequest.cpp \
	FlxMouseHolder.cpp \
	FlxShader.cpp \
	FlxU.cpp \
	FlxVirtualKeyboard.cpp \
	tweener/CppTween.cpp \
	backend/sdl_mobile/Backend.cpp

LOCAL_CFLAGS := -DFLX_MOBILE --std=gnu++0x
LOCAL_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

