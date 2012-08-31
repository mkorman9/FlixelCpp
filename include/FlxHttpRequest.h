/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_HTTPREQUEST_H_
#define _FLX_HTTPREQUEST_H_

#include "backend/cpp.h"

// request type
enum FlxRequestType {
    FLX_HTTP_GET,
    FLX_HTTP_POST
};


/*
*  HTTP response structure
*/
struct FlxHttpResponse {
    std::map<std::string, std::string> header;
    int code;
    std::string data;
};

/*
*  HTTP request builder
*/
class FlxHttpRequest {

public:
    std::string host, postData, resource;
    std::map<std::string, std::string> header;
    int port;
    FlxRequestType method;

    FlxHttpRequest(FlxRequestType method = FLX_HTTP_GET, const std::string& resource = "/",
                   const std::string& host = "", int port = 80);

    bool send(FlxHttpResponse& resp);


};

#endif




