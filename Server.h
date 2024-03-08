
#pragma once
#define SERVER_H
#include <iostream>
#include <winsock2.h>
#include <string>
#include <functional>
#include <vector>
#include <stdlib.h>
#include <map>
#include "Response.h"
#include "Request.h"
#include <any>
#include <variant>
#include "JSONParser.h"
#include <sstream>

#include <typeinfo>

enum HttpMethod
{
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE,
    HTTP_PATCH
};

struct ParamKey
{
    std::string key;
    std::string value;
};
struct Header
{
    std::string key;
    std::string value;
};

template <typename T>
class Route
{
public:
    HttpMethod method;
    ParamKey path1param;
    ParamKey path2param;
    ParamKey path3param;
    ParamKey path4param;

    bool secure;
    std::function<Response(const Request<T> req)> handler;
    std::function<AuthResponse(const Request<T> req)> authhandler;

    Route(const HttpMethod &method, const ParamKey &path1param, const ParamKey &path2param, const ParamKey &path3param, const ParamKey &path4param, bool secure, const std::function<Response(const Request<T> req)> &handler, const std::function<AuthResponse(const Request<T> req)> &authhandler)
        : method(method), path1param(path1param), path2param(path2param), path3param(path3param), path4param(path4param), secure(secure), handler(handler), authhandler(authhandler){};
    Route(const HttpMethod &method, const ParamKey &path1param, const ParamKey &path2param, const ParamKey &path3param, const ParamKey &path4param, bool secure, const std::function<Response(const Request<T> req)> &handler)
        : method(method), path1param(path1param), path2param(path2param), path3param(path3param), path4param(path4param), secure(secure), handler(handler){};
};

template <typename T>
class Server
{
private:
    SOCKET serverSocket;
    std::vector<Route<T>> route;
    SOCKADDR_IN sc;

public:
    Server(int port);

    void Get(std::string path, std::function<AuthResponse(const Request<T> req)> authHandler, std::function<Response(const Request<T> req)> method, bool auth = true);
    void Get(std::string path, std::function<Response(const Request<T> req)> method, bool auth = false);

    // template <typename K>

    void Post(std::string path, std::function<AuthResponse(const Request<T> req)> authHandler, std::function<Response(const Request<T> req)> method, bool auth = true);
    void Post(std::string path, std::function<Response(const Request<T> req)> method, bool auth = false);
    int Start();
    ~Server();
};
