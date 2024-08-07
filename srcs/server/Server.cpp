/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:35:39 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/07 13:27:23 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


/* CONSTRUCTOR / DESTRUCTOR ************************************************** */

Server::Server()
{
}

Server::~Server()
{
}


/* GETTERS/SETTERS ****************************************************************** */

void Server::setPort(int port)
{
	_port = port;
}

void Server::setPassword(const std::string& password)
{
	_password = hashPassword(password);
}


/* HASH PASSWORD************************************************************* */

bool Server::verifyPassword(const std::string& password) const
{
	return hashPassword(password) == _password;
}

std::string Server::hashPassword(const std::string& password) const
{
	unsigned long hash = 5381;
	for (size_t i = 0; i < password.size(); ++i) {
		hash = ((hash << 5) + hash) + passw ord[i]; // hash * 33 + c
	}

	std::ostringstream oss;
	oss << std::hex << hash;
	return oss.str();
}

/* ************************************************************************** */


/* RUN ****************************************************************** */

void Server::run()
{
	/* ORDER OF WHAT IT SHOULD HAPPEN IN THE RUN FUNCTION
	// Create the socket
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
		throw std::runtime_error("Failed to create the socket");
	// Bind the socket
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(_port);
	if (bind(_socket, (struct sockaddr*)&_addr, sizeof(_addr)) == -1)
		throw std::runtime_error("Failed to bind the socket");
	// Listen for connections
	if (listen(_socket, 10) == -1)
		throw std::runtime_error("Failed to listen for connections");
	// Accept connections
	struct sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	int clientSocket = accept(_socket, (struct sockaddr*)&clientAddr, &clientAddrSize);
	if (clientSocket == -1)
		throw std::runtime_error("Failed to accept the connection");
	// Receive data
	char buffer[1024];
	int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (bytesRead == -1)
		throw std::runtime_error("Failed to receive data");
	// Send data
	if (send(clientSocket, buffer, bytesRead, 0) == -1)
		throw std::runtime_error("Failed to send data");
	// Close the connection
	close(clientSocket);
	// Close the socket
	close(_socket);*/

	while (1)
	{
		// Accept new connections
		socket();
		bind();
		listen();
		accept();
		receive();
		send();
		close();
		// Read from the connections
		// Parse the commands
		// Execute the commands
		// Send the response
	}
}
