/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:35:39 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/13 15:18:21 by ofadhel          ###   ########.fr       */
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
	return hashPassword(password) ==_password;
}

std::string Server::hashPassword(const std::string& password) const
{
	unsigned long hash = 5381;
	for (size_t i = 0; i < password.size(); ++i) {
		hash = ((hash << 5) + hash) + password[i]; // hash * 33 + c
	}

	std::ostringstream oss;
	oss << std::hex << hash;
	return oss.str();
}

/* ************************************************************************** */


/* RUN ****************************************************************** */

void Server::run()
{
	//ORDER OF WHAT IT SHOULD HAPPEN IN THE RUN FUNCTION
	/*tcp_serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	DESCRIPTION
	This is an implementation of the TCP protocol defined in RFC 793,
	RFC 1122 and RFC 2001 with the NewReno and SACK extensions.
	It provides a reliable, stream-oriented, full-duplex connection
	between two sockets on top of ip(7), for both v4 and v6 versions.
	TCP guarantees that the data arrives in order and retransmits lost packets.
	It generates and checks a per-packet checksum to catch transmission errors.
	TCP does not preserve record boundaries.
	A newly created TCP socket has no remote or local address and is not fully specified.
	To create an outgoing TCP connection use connect(2) to establish a connection to another TCP socket.
 	To receive new incoming connections, first bind(2) the socket to a local address and port and then call listen(2)
	to put the socket into the listening state. After that a new socket for each incoming connection
	can be accepted using accept(2). A socket which has had accept(2) or connect(2) successfully
	called on it is fully specified and may transmit data.
	Data cannot be transmitted on listening or not yet connected sockets.*/

	// Create the socket
	// socketfd: It is the file descriptor for the socket.
	// AF_INET6: It specifies the IPv6 protocol family.
	// SOCK_STREAM: It defines that the TCP type socket.

	_serverSocket = socket(AF_INET, SOCK_STREAM, 0); //tcp socket v6
	if (_serverSocket == -1)
		throw std::runtime_error("Failed to create the socket");

	//setting server to allow multiple connections

	int opt = 1;
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Failed to set socket options");


	//We then define the server address using the following set of statements
	/*sockaddr_in: It is the data type that is used to store the address of the socket. SEE SERVER.HPP
	htons(): This function is used to convert the unsigned int from machine byte order to network byte order.
	INADDR_ANY: It is used when we don’t want to bind our socket to any particular IP and instead make it listen to all the available IPs.*/

	std::memset(&_serverAddr, 0, sizeof(_serverAddr));
	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_addr.s_addr = INADDR_ANY;
	_serverAddr.sin_port = htons(_port);

	//fcntl(_serverSocket, F_SETFL, O_NONBLOCK); //non blocking

	if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Failed to set socket to non-blocking");

	//Then we bind the socket using the bind() call as shown.

	if (bind(_serverSocket, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) == -1)
		throw std::runtime_error("Failed to bind the socket");

	// We then tell the application to listen to the socket refffered by the serverSocket.

	if (listen(_serverSocket, 50) == -1)
		throw std::runtime_error("Failed to listen for connections");

	// Accepting a Client Connection

	fd_set readfds;
	int maxfds = _serverSocket;

	std::cout << "waiting for a client to connect" << std::endl;
	while (1)
	{
		FD_ZERO(&readfds);
		FD_SET(_serverSocket, &readfds);

		// Add all client sockets to the fd_set
		for (size_t i = 0; i < _newfds.size(); ++i)
		{
			FD_SET(_newfds[i], &readfds);
			if (_newfds[i] > maxfds)
				maxfds = _newfds[i];
		}

		//The select() call is used to monitor multiple file descriptors,
		//waiting until one or more of the file descriptors become "ready" for some class of I/O operation.

		if (select(maxfds + 1, &readfds, NULL, NULL, NULL) == -1)
			throw std::runtime_error("Failed to select the socket");

		// Check if there is activity on the server socket (new connection)
		//The FD_ISSET() macro is used to check if a file descriptor is part of the set of file descriptors passed to the select() call.
		//The accept() call is used to accept the connection request that is recieved on the socket the application was listening to.
		if (FD_ISSET(_serverSocket, &readfds))
		{
			struct sockaddr_in _clientAddr;
			socklen_t clientAddrSize = sizeof(_clientAddr);
			int clientSocket = accept(_serverSocket, (struct sockaddr*)&_clientAddr, &clientAddrSize);
			if (clientSocket == -1)
				throw std::runtime_error("Failed to accept the connection");

			_newfds.push_back(clientSocket);
			//_clients.push_back(new Client(clientSocket)); //maybe after recv so can receive password, check and then can add
			std::cout << "new client accepted. FD is: " << clientSocket << " from : " << inet_ntoa(_clientAddr.sin_addr) << ":" << ntohs(_clientAddr.sin_port) << std::endl;
		}


		// Check activity on client sockets
		/*Then we start receiving the data from the client.
		We can specify the required buffer size so that it has enough space
		to receive the data sent the the client. The example of this is shown below.
		*/

		for (size_t i = 0; i < _newfds.size(); ++i)
		{
			int clientSocket = _newfds[i];
			if (FD_ISSET(clientSocket, &readfds))
			{
				char buffer[1024];
				int readSize = recv(clientSocket, buffer, sizeof(buffer), 0);

				if (readSize == -1)
					throw std::runtime_error("Failed to read from the socket");
				else if (readSize == 0)
				{
					std::cout << "Client disconnected. FD = " << clientSocket << std::endl;
					close(clientSocket);
					_newfds.erase(_newfds.begin() + i);
					for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
						{
							if ((*it)->getFd() == clientSocket)
							{
								_clients.erase(it);
								break;
							}
						}
					--i; // Adjust index after removal
				}
				else
				{
					buffer[readSize - 1] = '\0'; // Null-terminate the buffer

					//std::cout << "Received: " << buffer << " from client " << clientSocket << std::endl;

					std::string command(buffer); // Example command handling
					std::string data; // Parse data from command as needed

					if (command.substr(0, 4) == "PASS")
					{
						int logged = -1;
						for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
						{
							if ((*it)->getFd() == clientSocket)
							{
								send(clientSocket, "You're already logged in\n", 26, 0);
								logged = 0;
								break;
							}
						}
						if (logged == -1)
						{
							data = command.substr(5);
							if (verifyPassword(data))
							{
								send(clientSocket, "Password correct. You're now logged in\n", 39, 0);
								_clients.push_back(new Client(clientSocket));
							}
							else
							{
								send(clientSocket, "Password incorrect\n", 19, 0);
							}
						}
					}
					else
					{
						// Handle other commands
					}
				}
			}
		}

		//We can also send the data to the client using the send() call as shown below.

		/*if (send(clientSocket, buffer, readSize, 0) == -1)
			throw std::runtime_error("Failed to send to the socket");

		//We can also close the connection using the close() call as shown below.
		*/
	}
	close(_serverSocket);
}
