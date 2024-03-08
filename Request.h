#pragma once
#include <string>
#include <map>
template <typename T>
class Request {
public:
	std::map<std::string, std::string> params;
	std::map<std::string, std::string> headers;
	std::string query;
	 T body;
	Request() : body() {}
};