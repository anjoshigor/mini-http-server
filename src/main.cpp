#include <iostream>
#include <thread>
#include <exception>
#include <vector>
#include "logger.hpp"
#include "socket.h"
#include "http.h"

void handle_client(Socket *socket, long client);

int main(int argc, char const *argv[]) {
	std::vector<std::thread> threads;

#ifdef PORT
	Socket socket {PORT};
	std::clog<<"listening on port "<<PORT<<"..."<<std::endl;
#else
	Socket socket {8080};
	std::clog<<"listening on port 8080..."<<std::endl;
#endif

	try {
		socket.bind();
		socket.listen();

		while(true){
			int client = socket.accept();
			threads.push_back(std::thread(handle_client, &socket, client));
		}
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}


void handle_client(Socket* socket, long client){
	std::clog << "---------------------------------------------" << std::endl;
	std::clog << "Handling client..." <<std::endl;

	std::string incoming;
	socket->receive(client, &incoming);

	std::clog << incoming << std::endl;

	std::string info {"Client IP: " + socket->get_client_ip()+ "\n" + http::get_current_date()};
	Logger::get_instance().sys_register((info+incoming), Logger::INFO);

	std::clog << "Request:\n" << incoming << std::endl;

	std::string outcoming {http::parse_http(incoming)};
	socket->send(client, outcoming);

	std::clog << "Reponse:\n" << outcoming << std::endl;

	close(client);
	std::clog << "Client handled [OK]"<< std::endl;
	std::clog << "---------------------------------------------" << std::endl;
}
