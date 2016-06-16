#include <iostream>
#include "LogClass.hpp"
#include "socket.h"
#include "http.h"
#include <vector>
using std::string;

#define  PATTERN "GET HTTP/1.1 Host: Accept:" //must have a GET and a HTTP/1.1 in this order


void handle_client(Socket* socket, long client){
	std::clog<<"---------------------------------------------"<<std::endl;
	std::clog<<"Handling client..."<<std::endl;


	string outcoming, incoming;
	LogClass& logFile = LogClass::makeInstance("itdoesntmatter");

	socket->readSocket(client, &incoming);
	std::string info = "Client IP: "+socket->get_client_ip()+"\n"+http::get_current_date();
	logFile.WriterLog(info+incoming);

	std::clog<<"Request:\n"<<incoming<<std::endl;

	outcoming = http::parse_http(incoming, PATTERN);
	socket->writeSocket(client, outcoming);

	std::clog<<"Reponse:\n"<<outcoming<<std::endl;


	close(client);
	std::clog<<"Client handled [OK]"<<std::endl;
	std::clog<<"---------------------------------------------"<<std::endl;
}

int main(int argc, char const *argv[])
{

	LogClass& v = LogClass::makeInstance("log.txt");
	//creating server socket

	#ifdef PORT
	Socket socket {PORT};
	std::clog<<"listening to port "<<PORT<<std::endl;
	#else
	Socket socket {8080};
	std::clog<<"listening to port 8080"<<std::endl;
	#endif


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
