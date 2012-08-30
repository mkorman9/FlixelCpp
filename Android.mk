LOCAL_PATH := $(call my-dir)/src

include $(CLEAR_VARS)

LOCAL_MODULE := flixel

LOCAL_C_INCLUDES := jni/flixel/include

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
	FlxTilemap.cpp
	
LOCAL_CFLAGS := -DFLX_MOBILE

include $(BUILD_STATIC_LIBRARY)

