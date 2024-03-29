#include "PhotoSender.hpp"

void PhotoSender::connectToServer(const std::string& server_address, const std::string& port)
{
	ip::tcp::resolver resolver(io);
	connect(socket, resolver.resolve(server_address, port));
}

void PhotoSender::sendPhoto(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error: Cannot open." << std::endl;
		return;
	}

	std::vector<char> data((
		std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>()
	);

	size_t total_bytes_sent = 0;
	size_t data_size = data.size();
	size_t chunk_size = 1024;

	while (total_bytes_sent < data_size)
	{
		size_t remaining_bytes = data_size - total_bytes_sent;
		size_t current_chunk_size = std::min(chunk_size, remaining_bytes);

		write(socket, buffer(data.data() + total_bytes_sent, current_chunk_size));
		total_bytes_sent += current_chunk_size;
	}

	std::cout << "Photo send to the server." << std::endl;
}

void PhotoSender::listenToServer()
{
	try
	{
		while (true) {
			std::array<char, 1024> buffer;
			size_t bytes_received = socket.read_some(boost::asio::buffer(buffer));
			if (bytes_received > 0) {

			}
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception in listenToServer: " << e.what() << std::endl;
	}
}

void PhotoSender::run()
{
	io.run();
}