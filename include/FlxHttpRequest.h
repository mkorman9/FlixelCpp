/*
   This file is a part of "Flixel C++ port" project
   Copyrights (c) by Michał Korman 2012
*/
#ifndef _FLX_HTTPREQUEST_H_
#define _FLX_HTTPREQUEST_H_

#include "backend/cpp.h"

/**
*  Type of request. GET or POST
*/
enum FlxRequestType {
    FLX_HTTP_GET,
    FLX_HTTP_POST
};


/**
*  HTTP response
*/
struct FlxHttpResponse {

	/**
	*  Received HTTP headers
	*/
    std::map<std::string, std::string> header;
	
	/**
	*  Response code
	*/
    int code;
	
	/**
	*  Received data
	*/
    std::string data;
};


/**
*  HTTP request builder
*/
class FlxHttpRequest {

public:

	/**
	*  Host to connect and send in HTTP header
	*/
    std::string host;
	
	/**
	*  Data in POST section. <code>Content-Length</code> header will be set automatically.
	*/
	std::string postData;

	/**
	*  Resource to request (string after domain name in HTTP address)
	*/
	std::string resource;
	
	/**
	*  Headers to send
	*/
    std::map<std::string, std::string> header;
	
	/**
	*  Server port to connect
	*/
    int port;
	
	/**
	*  One of two supported HTTP methods
	*/
    FlxRequestType method;

	
	/**
	*  Default constructor.
	*  @param method HTTP method
	*  @param resource Resource to request
	*  @param host Host to connect and send in HTTP header
	*  @param port Port to connect
	*/
    FlxHttpRequest(FlxRequestType method = FLX_HTTP_GET, const std::string& resource = "/",
                   const std::string& host = "", int port = 80);

	/**
	*  Send request and wait for response.
	*  @param resp Reference to <code>FlxHttpResponse</code> object
	*  @return <code>true</code> on success, <code>false</code> on failure
	*/
    bool send(FlxHttpResponse& resp);


};

#endif

