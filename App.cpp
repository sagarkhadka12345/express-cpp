#include "Server.h"
#include "Response.h"
#include "Request.h"
#include "JSONParser.h"
#include <thread>
Response s(Request<JSON> req)
{
	std::string str = "Thank you";

	Response rs = Response();
	rs.message = str;
	rs.status = 200;
	return rs;
}

Response ss(Request<JSON> req)
{
	std::string str = "Thank you";

	Response rs = Response();
	rs.message = str;
	rs.status = 200;
	return rs;
}
Response server_message(Request<std::string> req)
{
	std::string str = "Thank you";

	Response rs = Response();
	rs.message = str;
	rs.status = 200;
	return rs;
}

Response auth(Request<std::string> req)
{

	std::string str = "Thank you";

	Response rs = Response();
	rs.message = str;
	rs.status = 200;
	return rs;
}

Response server_messagedobul(Request<double> req)
{
	std::string str = "Thank you";

	Response rs = Response();
	rs.message = str;
	rs.status = 200;
	return rs;
}
Response postResponse(Request<JSON> req)
{

	std::string str = "Thank you From Post";
	std::map<std::string, std::string>::const_iterator it = req.body.find("user_id");
	Response rs = Response();

	const std::pair<std::string, std::string> &Rs = *it;
	if (it != req.body.end())
	{

		rs.message = str + " " + it->first + " " + req.params["user_id"];
	}
	rs.status = 200;
	return rs;
}

int main()
{
	Server anotherServer = Server<JSON>(4000);
	Server anotherServer1 = Server<int>(5000);
	Server server = Server<std::string>(3000);
	Server serverx = Server<double>(9000);

	server.Get("/:user_id", server_message);
	server.Get("/user_id", server_message, server_message, true);

	serverx.Get("/:user_id", server_messagedobul);
	anotherServer.Get("/:user_id", s);
	anotherServer.Post("/", postResponse);

	std::thread thread1([&server]()
						{ server.Start(); });

	std::thread thread2([&anotherServer]()
						{ anotherServer.Start(); });
	std::thread thread3([&anotherServer1]()
						{ anotherServer1.Start(); });
	std::thread thread4([&serverx]()
						{ serverx.Start(); });

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();

	return 0;
}