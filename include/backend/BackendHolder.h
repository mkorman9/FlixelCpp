#ifndef _FLX_BACKEND_HOLDER_H_
#define _FLX_BACKEND_HOLDER_H_

#include "../FlxBackendBase.h"
#include "../FlxVector.h"

/*
*  Singleton holding current definition of backend
*/
class BackendHolder {

private:
    BackendHolder() { }
    FlxBackendBase *backend;
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
};

#endif
