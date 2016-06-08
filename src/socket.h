#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <iostream>

class Socket
{
public:
	Socket(const int port);
	~Socket();

	void bindSocket();
	void listenSocket();
	void createSocket();
	long acceptSocket();
	void readSocket(long client_description, std::string* buffer);
	void writeSocket(long client_description, std::string buffer);
	std::string get_client_ip();

private:
	int server_socket;
	struct sockaddr_in server;
	struct sockaddr_in connected_client;

};
