#pragma once

#include <map>
#include <string>


class AuthHeaders {
public:
    static std::map<std::string, std::string> GetAuthHeaders(const std::string& httpRequest);

};                                                                                                                                                                          