
#pragma once
#include <string>
#include <map>
#include <optional>

class Response {
public:
	int status;
	std::string message;
	Response() {
		this->status = 200;
		this->message = "Not Initialized";
	}
};

using AuthResponse = std::optional<Response>;
