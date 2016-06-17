#include "socket.h"

Socket::Socket(unsigned int port):
				address{AF_INET, htons(port), (INADDR_ANY), 0}
{
	server = socket(AF_INET, SOCK_STREAM, 0);
	if(server == -1)
		throw std::runtime_error("Error socket!");
} 

Socket::~Socket() { close(); }

int Socket::accept(void) {
	socklen_t size = sizeof(address_client);
	int acc = ::accept(server, reinterpret_cast<struct sockaddr*>(&address_client), 
					   &size);
	return acc;
}

void Socket::bind(void) const {
	int err = ::bind(server, reinterpret_cast<const struct sockaddr*> (&address),
					sizeof(address));
	if(err)
		throw std::runtime_error("Error bind!");  
}

void Socket::close(void) {
	int err = ::close(server);

	if(err == -1)
		throw std::runtime_error("Error close socket!"); 	
}

void Socket::connect(void) const {
	int err = ::connect(server, reinterpret_cast<const struct sockaddr*>(&address), 
					   sizeof(address));
	if(err)
		throw std::runtime_error("Error connect!"); 	
}

std::string Socket::get_ip(void) const {
	char* ip = inet_ntoa(address.sin_addr);
	return ip;
}

std::string Socket::get_client_ip(void) const {
	char* ip = inet_ntoa(address_client.sin_addr);
	return ip;	
}

void Socket::listen(void) const {
	int err = ::listen(server, 20);
	if(err)
		throw std::runtime_error("Socket inactive!");  		
}

void Socket::receive(long description, std::string* buffer) {
	char tmp[BYTES];
	int err = read(description, tmp, BYTES);

 	if(err == -1)
 		throw std::runtime_error("Error receive!");

 	*buffer = tmp;
}

void Socket::send(long description, std::string& buffer) const {
	int err = write(description, &buffer[0], buffer.length());

 	if(err == -1)
 		throw std::runtime_error("Error send!"); 	
}
