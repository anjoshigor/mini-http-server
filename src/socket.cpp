#include "socket.h"

Socket::Socket(const int port): server_socket(0){
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server.sin_zero), 8);
}

Socket::~Socket(){
	close(server_socket);
}

void Socket::bindSocket(){
	int flag = bind(server_socket, reinterpret_cast<struct sockaddr*> (&server), sizeof(server));

	if(flag){
		std::cerr<<"Bind Error !"<<std::endl;
		exit(1);
	}
}

void Socket::listenSocket(){
	std::clog<<"Lisntening..."<<std::endl;
	int flag = listen(server_socket, 20);

	if(flag){
		std::cerr<<"ListenError"<<std::endl;
		exit(1);
	}
}

void Socket::createSocket(){
	server_socket = socket(AF_INET,SOCK_STREAM,0);
	std::clog<<"Socket Created"<<std::endl;
}

long Socket::acceptSocket(){
	std::clog<<"Accept socket"<<std::endl;
	socklen_t size = sizeof(connected_client);
	long client_port = accept(server_socket,(struct sockaddr *)&connected_client,&size);
	return client_port;
}

void Socket::readSocket(long client_description, std::string* buffer){
	char tempbuffer[2096];
	read(client_description, tempbuffer, sizeof(tempbuffer));
	*buffer = tempbuffer;
}

void Socket::writeSocket(long client_description, std::string buffer){
	write(client_description, &buffer[0], sizeof(char)*buffer.size());
}

std::string Socket::get_client_ip(){
	char* ip = inet_ntoa(connected_client.sin_addr);
	std::string ip_client (ip);

	return ip_client;
}
