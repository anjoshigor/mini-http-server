#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
//#include <exception> for g++ 5+
#include <stdexcept>
#include <iostream>

#define BYTES 	10240

class Socket {
private:
	//data members
	struct sockaddr_in address;
	struct sockaddr_in address_client;
	int server;

public:
	//constructor
	Socket(unsigned int port);
	//destructor
	~Socket();
	//functions members
	int accept();
	void bind() const;
	void close();
	void connect() const;
	std::string get_ip() const;
	std::string get_client_ip() const;
	void listen() const;
	void receive(long description, std::string* buffer);
	void send(long description, std::string& buffer) const;
};

#endif //SOCKET_H
