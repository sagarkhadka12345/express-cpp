#pragma once

#include <map>
#include <string>


class JSONParser {
public:
    static std::map<std::string, std::string> json(std::string requestBody);

};


using JSON = std::map<std::string, std::string>;





