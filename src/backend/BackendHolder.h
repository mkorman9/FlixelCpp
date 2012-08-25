#ifndef _FLX_BACKEND_HOLDER_H_
#define _FLX_BACKEND_HOLDER_H_

#include "../FlxBackendBase.h"
#include "../FlxVector.h"

/*
*  Singleton holding current definition of backend
*/
class BackendHolder {

private:
    BackendHolder() { timeModification = 1; }
    FlxBackendBase *backend;
    FlxVector scaleRatio;
    FlxVector scroolVector;
    float timeModification;
public:

    static BackendHolder& get() {
        static BackendHolder instance;
        return instance;
    }

    void setBackend(FlxBackendBase *back) {
        backend = back;
    }

    FlxBackendBase *getBackend() {
        return backend;
    }

    void setScalingRatio(float x, float y) {
        scaleRatio.x = x;
        scaleRatio.y = y;
    }

    FlxVector getScalingRatio() {
        return scaleRatio;
    }

    void setScrool(const FlxVector& move) {
        scroolVector.x = -move.x;
        scroolVector.y = -move.y;
    }

    FlxVector getScroolVector() {
        return scroolVector;
    }

    float getTimeModifier() {
        return timeModification;
    }

    void setTimeModifier(float mod) {
        if(mod == 0) mod = 1;

        timeModification = mod;
    }
};

#endif
