#pragma once

#include <iostream>
#include <winsock2.h>
#include <string>
#include <functional>
#include <vector>
#include <stdlib.h>
#include <map>
#include <variant>
#include <sstream>
#include "AuthHeaders.h"
std::map<std::string, std::string> AuthHeaders::GetAuthHeaders(const std::string &httpRequest)
{
    std::map<std::string, std::string> headers;

    std::istringstream ss(httpRequest);
    std::string line;

    while (std::getline(ss, line) && !line.empty())
    {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos)
        {
            std::string headerName = line.substr(0, colonPos);
            std::string headerValue = line.substr(colonPos + 1);
            // Trim leading and trailing whitespace
            headerName.erase(0, headerName.find_first_not_of(" \t\r\n"));
            headerName.erase(headerName.find_last_not_of(" \t\r\n") + 1);
            headerValue.erase(0, headerValue.find_first_not_of(" \t\r\n"));
            headerValue.erase(headerValue.find_last_not_of(" \t\r\n") + 1);
            headers[headerName] = headerValue;
        }
    }

    return headers;
}