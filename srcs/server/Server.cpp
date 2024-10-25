/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:35:39 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/25 22:37:26 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"


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

int Server::getPort() const
{
	return _port;
}

Client* Server::getClient(int clientSocket)
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->getFd() == clientSocket)
			return _clients[i];
	}
	return 0;
}

int Server::getClientIndex(int clientSocket)
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->getFd() == clientSocket)
			return i;
	}
	return -1;
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



// Method to remove and delete a client by socket
void Server::removeClient(int clientSocket)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if ((*it)->getFd() == clientSocket)
		{
			delete *it; // Free the dynamically allocated Client
			_clients.erase(it); // Erase from the vector
			break;
		}
	}
}

/* ************************************************************************** */


/* RUN ****************************************************************** */

/*RDER OF WHAT IT SHOULD HAPPEN IN THE RUN FUNCTION
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
	Data cannot be transmitted on listening or not yet connected sockets.
*/

void Server::createSocket()
{
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

	// Add the server socket to the list of file descriptors to monitor

	socketdata newfd;
	newfd.id = _serverSocket;
	_newfds.push_back(newfd);
}

void Server::run()
{
	createSocket();

	fd_set readfds;
	int maxfds = _serverSocket;
	std::cout<<"limit defined "<<maxfds<<std::endl;
	std::cout << BOLD << CYAN << "IRC SERVER UP! WAITING FOR CLIENTS" << RESET << std::endl;
	startLoop(readfds, maxfds);
	//killServer();  //kill server close all sockets and free memory
}

//per dopo da sistemare le interazioni qua
Channel*	Server::getChannel(std::string& channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == channelName)
			return &_channels[i];
	}
	return 0;
}


int	Server::isInServer(Channel *channel)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == channel->getName())
			return 1;
	}
	return 0;
}
