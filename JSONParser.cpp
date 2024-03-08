#include <map>
#include <string>
#include "JSONParser.h"

std::map<std::string, std::string> JSONParser::json(std::string requestBody) {


	std::map<std::string, std::string> requestJSON;
	bool parsingKey = false;
	bool parsingValue = false;
	bool insideString = false;
	int pos = 0;
	std::string key, value;

	for (char c : requestBody) {

		if (c == '"') {
			if (pos == 3) {
				pos = 0;
				requestJSON[key] = value;
				key.clear();
				value.clear();
			}
			else {
				pos += 1;
			}
		}
		else if (c == '{' || c == '}') {

		}
		else if (pos == 1 && c != ' ' && c != '\n' && c != '\r') {
			key += c;
		}
		else if (pos == 3 && c != ' ' && c != '\n' && c != '\r') {
			value += c;
		}

	}
	return requestJSON;
}











