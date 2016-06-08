#include <iostream>
#include "LogClass.hpp"
#include "socket.h"
#include "http.h"
#include <vector>
#define PATTERN "GET HTTP/1.1" //must have a GET and a HTTP/1.1 in this order

using std::string;


void handle_client(Socket* socket, long client){
	std::clog<<"---------------------------------------------"<<std::endl;
	std::clog<<"Handling client..."<<std::endl;


	string outcoming, incoming;
	LogClass& logFile = LogClass::makeInstance("itdoesntmatter");

	socket->readSocket(client, &incoming);

	logFile.WriterLog(incoming+socket->get_client_ip());

	std::clog<<"++++++++++++++++++++++++++++++++"<<std::endl;
	std::clog<<"Request:\n"<<incoming<<std::endl;
	std::clog<<"++++++++++++++++++++++++++++++++"<<std::endl;

	outcoming = http::parse_http(incoming, PATTERN);
	socket->writeSocket(client, outcoming);
	std::clog<<"++++++++++++++++++++++++++++++++"<<std::endl;
	std::clog<<"Reponse:\n"<<outcoming<<std::endl;
	std::clog<<"++++++++++++++++++++++++++++++++"<<std::endl;

	close(client);
	std::clog<<"Client handled [OK]"<<std::endl;
	std::clog<<"---------------------------------------------"<<std::endl;
}

int main(int argc, char const *argv[])
{

	LogClass& v = LogClass::makeInstance("log.txt");
	//creating server socket
	Socket socket {8080};
	socket.createSocket();
	socket.bindSocket();
	socket.listenSocket();

	std::vector<std::thread> threads;

	while(true){
		long client = socket.acceptSocket();
		threads.push_back(std::thread(handle_client,&socket,client));
	}

	delete&v;



	return 0;
}