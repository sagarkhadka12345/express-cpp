
#include "Server.h"
#include "AuthHeaders.h"

template <typename T> 
bool findByNameAndAddress(const Route<T>& route, const HttpMethod& httpMethod,
	const std::string& path) {

	std::istringstream iss(path);
	std::string paths[] = { "","","","" };
	std::string token;
	int i = 0;
	while (std::getline(iss, token, '/')) {
		if (!token.empty()) { // Skip empty paths
			paths[i] = '/' + token;
			i++;
			// Add '/' back to each non-empty token
		}

	}
	return (route.method == httpMethod) && (route.path1param.key == paths[0] || route.path1param.key == "*") &&
		(route.path2param.key == paths[1] || route.path2param.key == "*") && (route.path3param.key == paths[2] ||
			route.path3param.key == "*") && (route.path4param.key == paths[3] || route.path4param.key == "*");
}

template <typename T>
bool findByAddress(const Route<T>& route,
	const std::string& path) {


	std::istringstream iss(path);
	std::string paths[] = { "","","","" };
	std::string token = "/";
	int i = 0;
	while (std::getline(iss, token, '/')) {
		if (!token.empty()) { // Skip empty paths
			paths[i] = '/' + token;
			i++;
			// Add '/' back to each non-empty token
		}
	}
	return  (route.path1param.key == paths[0] || route.path1param.key == "*") &&
		(route.path2param.key == paths[1] || route.path2param.key == "*") && (route.path3param.key == paths[2] || route.path3param.key == "*") &&
		(route.path4param.key == paths[3] || route.path4param.key == "*");
}



template <typename T>
Server<T>::Server(int port) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed" << std::endl;

	}

	// Create a socket
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		std::cerr << "Error creating socket" << std::endl;

	}

	// Bind the socket to a specific IP and port
	this->sc = SOCKADDR_IN();
	sc.sin_family = AF_INET;
	sc.sin_addr.s_addr = INADDR_ANY;
	sc.sin_port = port;
	SOCKADDR_IN serverAddr = this->sc;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port); // Example port

	if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "Bind failed" << std::endl;

	}


	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "Listen failed" << std::endl;

	}

	std::cout << "Listening for incoming connections..." << std::endl;


}

template <typename T>
void Server<T>::Get(std::string path, std::function<AuthResponse(const Request<T> req)> authHandler, std::function<Response(const Request<T> req)> method, bool auth )
{


	std::istringstream iss(path);
	std::string paths[] = { "","","","" };
	std::string params[] = { "","","","" };
	std::string token;
	int i = 0;
	while (std::getline(iss, token, '/')) {
		if (!token.empty()) {
			size_t found = token.find(":");
			if (found != std::string::npos) {
				token.erase(found, 1);
				params[i] = token;
				paths[i] = '*';
			}
			else {

				paths[i] = '/' + token;
			}
		}
	}

	

	Route<T> route = Route<T> {
		HTTP_GET,
		{paths[0], params[0]},
		{paths[1], params[1]},
		{paths[2], params[2]},
		{paths[3], params[3]},
		
		 auth,
		 method,
		  authHandler 
	};
	

	this->route.push_back(route);

}




template <typename T>
void Server<T>::Get(std::string path, std::function<Response(const Request<T> req)> method,  bool auth)
{


	std::istringstream iss(path);
	std::string paths[] = { "","","","" };
	std::string params[] = { "","","","" };
	std::string token;
	int i = 0;
	while (std::getline(iss, token, '/')) {
		if (!token.empty()) {
			size_t found = token.find(":");
			if (found != std::string::npos) {
				token.erase(found, 1);
				params[i] = token;
				paths[i] = '*';
			}
			else {

				paths[i] = '/' + token;
			}
		}
	}
	std::map < std::string, std::string > headers;
	Route<T> route = Route<T>(
		HTTP_GET,
		{paths[0], params[0]},
		{paths[1], params[1]},
		{paths[2], params[2]},
		{paths[3], params[3]},
		
		 auth,
		 method
		  
	);


	this->route.push_back(route);


	

}




template <typename T>
void Server<T>::Post(std::string path,  std::function<AuthResponse(const Request<T> req)> authHandler, std::function<Response(const Request<T> req)> method, bool auth)
{

	std::istringstream iss(path);
	std::string paths[] = { "","","","" };
	std::string params[] = { "","","","" };
	std::string token;
	int i = 0;
	while (std::getline(iss, token, '/')) {
		if (!token.empty()) { // Skip empty paths
			size_t found = token.find(":");
			if (found != std::string::npos) {
				token.erase(found, 1);
				params[i] = token;
				paths[i] = '*';
			}
			else {

				paths[i] = '/' + token;
			}
		}
	}

	std::map < std::string, std::string > headers;
	Route<T> route = Route<T> (
		HTTP_POST,

		  {paths[0], params[0]},
		{paths[1], params[1]},
		{paths[2], params[2]},
		{paths[3], params[3]},
		
		auth,
		 method,
		 authHandler
	);
	

	this->route.push_back(route);
}




template <typename T>
void Server<T>::Post(std::string path, std::function<Response(const Request<T> req)> method, bool auth)
{



	std::istringstream iss(path);
	std::string paths[] = { "","","","" };
	std::string params[] = { "","","","" };
	std::string token;
	int i = 0;
	while (std::getline(iss, token, '/')) {
		if (!token.empty()) { // Skip empty paths
			size_t found = token.find(":");
			if (found != std::string::npos) {
				token.erase(found, 1);
				params[i] = token;
				paths[i] = '*';
			}
			else {

				paths[i] = '/' + token;
			}
		}
	}
	
	Route route = Route<T>(
	HTTP_POST,

	  {paths[0], params[0]},
	{paths[1], params[1]},
	{paths[2], params[2]},
	{paths[3], params[3]},
	
	auth,
	 method
	 
	);


	this->route.push_back(route);

}




template <typename T>
int Server<T>::Start()
{

	while (true)
	{
		// Accept client connections
		SOCKADDR_IN clientAddr = this->sc;
		int clientAddrLen = sizeof(clientAddr);
		SOCKET clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrLen);

		if (clientSocket == INVALID_SOCKET)
		{
			std::cerr << "Accept failed" << std::endl;
			return 1;

		}
		std::string requestBody;

		char buffer[4096];
		int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);




		// Process the HTTP request and construct an appropriate response
		std::string httpRequest(buffer, bytesRead);

		// Read and handle HTTP requests

		size_t contentLength = 0;
		size_t contentLengthPos = httpRequest.find("Content-Length: ");
		if (contentLengthPos != std::string::npos) {
			contentLengthPos += 16; // Length of "Content-Length: "
			size_t endOfLinePos = httpRequest.find("\r\n", contentLengthPos);
			if (endOfLinePos != std::string::npos) {
				std::string contentLengthStr = httpRequest.substr(contentLengthPos, endOfLinePos - contentLengthPos);
				contentLength = std::stoi(contentLengthStr);
			}
		}
		if (bytesRead > 0)
		{
			try
			{
				std::string requestHeaders;


				while ((bytesRead) > 0) {
					requestHeaders.append(buffer, bytesRead);

					// Check for the end of the headers, which is marked by an empty line (double CRLF).
					size_t doubleCrlfPos = requestHeaders.find("\r\n\r\n");
					if (doubleCrlfPos != std::string::npos) {
						// Extract the headers portion of the data
						std::string headers = requestHeaders.substr(0, doubleCrlfPos);

						// Extract the request body, which follows the double CRLF
						requestBody = requestHeaders.substr(doubleCrlfPos + 4);

						// Now, you have the request body in the 'requestBody' string
						break;  // Exit the loop after reading the request body
					}
				}


				// Extract the path from the request
				size_t methodEnd = httpRequest.find(' ');

				size_t pathStart = methodEnd != std::string::npos ? httpRequest.find('/', methodEnd) : std::string::npos;
				size_t pathEnd = pathStart != std::string::npos ? httpRequest.find(' ', pathStart) : std::string::npos;


				std::string requestMethod = httpRequest.substr(0, methodEnd);
				std::string requestPath = httpRequest.substr(pathStart, pathEnd - pathStart);

				HttpMethod httpMethod;
				auto requestJSON = JSONParser::json(requestBody);
				if (requestMethod == "GET") {

					httpMethod = HTTP_GET;
				}
				else if (requestMethod == "POST") {
					httpMethod = HTTP_POST;

				}
				else if (requestMethod == "PATCH") {
					httpMethod = HTTP_PATCH;

				}
				else if (requestMethod == "DELETE") {
					httpMethod = HTTP_DELETE;

				}
				else if (requestMethod == "PUT") {
					httpMethod = HTTP_PUT;

				}
				else {

					httpMethod = HTTP_GET;
				}





				auto it = std::find_if(route.begin(), route.end(), [&](const Route<T>& p) {
					return findByNameAndAddress(p, httpMethod, requestPath);
					});

				bool n = it == route.end();

				if (n) {

					auto its = std::find_if(route.begin(), route.end(), [&](const Route<T>& p) {
						return findByAddress(p, requestPath);
						});

					bool m = its == route.end();
					if (m) {
						std::string httpResponse = "HTTP/1.1 " + std::to_string(400) + " Bad Request\r\n";
						httpResponse += "Content-Length: " + std::to_string(14) + "\r\n";
						httpResponse += "\r\n";  // Empty line to indicate the end of headers
						httpResponse += "No Route Found";
						send(clientSocket, httpResponse.c_str(), (int)httpResponse.size(), 0);
						closesocket(clientSocket);
					}
					else {

						std::string httpRes = "HTTP/1.1 " + std::to_string(400) + " Bad Request\r\n";
						httpRes += "Content-Length: " + std::to_string(14) + "\r\n";
						httpRes += "\r\n";  // Empty line to indicate the end of headers
						httpRes += "Invalid method";
						send(clientSocket, httpRes.c_str(), (int)httpRes.size(), 0);
						closesocket(clientSocket);
					}
				}
				else {
					const Route<T>& routeFound = 
						std::any_cast<Route<T>>(*it);
					std::istringstream iss(requestPath);

					std::string params[] = { "","","","" };
					std::string token;
					int i = 0;
					while (std::getline(iss, token, '/')) {
						if (!token.empty()) {


							params[i] = token;
						}
					}
					std::map<std::string, std::string>m = {
						{routeFound.path1param.value , params[0]},
						{routeFound.path2param.value, params[1]},
						{routeFound.path3param.value, params[2]},
						{routeFound.path4param.value, params[3] }


					};
					

					
					Request<T> req ;

					req.headers = AuthHeaders::GetAuthHeaders(httpRequest);
					req.params = m;
					req.query = std::string("");
					
					if constexpr (std::is_same<T, JSON>::value) {
					
						req.body = requestJSON;
					}
					else if constexpr (std::is_same<T, std::string>::value) {

						req.body = requestBody;
					}
					else if constexpr (std::is_same<T, std::string>::value) {

						req.body = requestBody;
					}
					else {
						
						throw std::exception("Type not found");
					}


					if (routeFound.secure ) {
						routeFound.authhandler(req);
					}
					auto x = routeFound.handler(req);
					std::string httpR = "HTTP/1.1 " + std::to_string(x.status) + " Bad Request\r\n";
					httpR += "Content-Length: " + std::to_string(x.message.length()) + "\r\n";
					httpR += "\r\n";  // Empty line to indicate the end of headers
					httpR += x.message;

					// Send the HTTP response
					send(clientSocket, httpR.c_str(), static_cast<int>(httpR.size()), 0);
					closesocket(clientSocket);

				}

			}


			catch (const std::exception& x)
			{

				std::string httpR = "HTTP/1.1 " + std::to_string(500)+ " Bad Request\r\n";
				httpR += "Content-Length: " + std::to_string(strlen( x.what())) + "\r\n";
				httpR += "\r\n";  // Empty line to indicate the end of headers
				httpR += x.what();

				// Send the HTTP response
				send(clientSocket, httpR.c_str(), static_cast<int>(httpR.size()), 0);
				closesocket(clientSocket);
			}

		}
		closesocket(clientSocket);
		// Close the client connection

	}
	WSACleanup();
}
template <typename T>
Server<T>::~Server()
{


}


template class Server<JSON>;
template class Server<std::string>;
template class Server<int>;template class Server<double>;

