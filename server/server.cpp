#include <stdio.h> 
#include <stdlib.h> 
#include <string> 
#include <iostream>

#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

class Certificate
{
private:
	std::string name;
	unsigned int hash;
public:
	Certificate(const std::string& n, int val) : name(n), hash(val) {}
	std::string toString() {
		std::string response = name + ";" + std::to_string(hash);
		return response;
	}
};

const int PORT = 8080;

void initWinSock()
{
	printf("\nInitialising Winsock...");
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(1);
	}

	printf("Initialised\n");
}

int main()
{
	int server_fd = 0;
	int new_socket = 0;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	const char *hello = "Hello from server";

	Certificate c("www.localhost.com", 1234);
	std::string certificateSerialized = c.toString();

	initWinSock();

	// Create socket descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Attach socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address,
		sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	// Setup listen queue
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for connection...\n");
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
		&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	printf("Sending certificate information\n");
	send(new_socket, certificateSerialized.c_str(), sizeof(certificateSerialized), 0);

	printf("Waiting for data...\n");
	recv(new_socket, buffer, 1024, 0);
	printf("Received: %s\n", buffer);

	send(new_socket, hello, strlen(hello), 0);
	printf("Hello message sent\n");

	return 0;
}
