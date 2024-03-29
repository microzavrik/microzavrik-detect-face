#ifndef PHOTO_SENDER
#define PHOTO_SENDER

#include <iostream>
#include <boost/asio.hpp>
#include <fstream>

using namespace boost::asio;

class PhotoSender
{
private:
	io_context io;
	ip::tcp::socket socket;
public:
	PhotoSender() : socket(io) { }

	void connectToServer(const std::string& server_address, const std::string& port);
	void sendPhoto(const std::string& filename);
	void listenToServer();
	void run();
};

#endif