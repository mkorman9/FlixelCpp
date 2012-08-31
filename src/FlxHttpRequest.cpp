#include "FlxHttpRequest.h"
#include "backend/BackendHolder.h"

FlxHttpRequest::FlxHttpRequest(FlxRequestType m, const std::string& r, const std::string& h, int p) {
    method = m;
    host = h;
    port = p;
    resource = r;

    header["Host"] = h;
    header["User-Agent"] = "FlixelCpp/1.0";
}


bool FlxHttpRequest::send(FlxHttpResponse& resp) {
    return BackendHolder::get().getBackend()->sendHttpRequest(this, resp);
}
