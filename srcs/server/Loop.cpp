/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:39:40 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/20 17:11:34 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

// Add all client sockets to the fd_set
	/*In the context of network programming, file descriptors are used to identify sockets.
	The select() system call, which is used later in the code, requires knowing the range of file descriptors to monitor.
	This range is determined by the highest file descriptor value plus one.

	The line if (_newfds[i] > maxfds) checks if the current client socket's file descriptor (_newfds[i]) is greater than the current value of maxfds.
	If it is, the maxfds variable is updated to this higher value. This ensures that maxfds always holds
	the highest file descriptor value among all the sockets being monitored. This is crucial for the select() call to function correctly,
	as it needs to know the upper limit of the file descriptors to check for activity.

	In summary, this line of code ensures that the maxfds variable is always set to the highest file descriptor value,
	which is necessary for the proper operation of the select() system call used to monitor multiple sockets
	for incoming data or connection requests.
*/

void Server::setMaxfds(int &maxfds, fd_set &readfds)
{
	FD_ZERO(&readfds);
	FD_SET(_serverSocket, &readfds);
	//maxfds = _serverSocket;

	for (size_t i = 0; i < _newfds.size(); ++i)
	{
		FD_SET(_newfds[i], &readfds);
		if (_newfds[i] > maxfds)
			maxfds = _newfds[i];
	}
}

void Server::startLoop(fd_set& readfds, int& maxfds)
{
	while (1)
	{
		setMaxfds(maxfds, readfds);

		//The select() call is used to monitor multiple file descriptors,
		//waiting until one or more of the file descriptors become "ready" for some class of I/O operation.
		int selectfd = select(maxfds + 1, &readfds, NULL, NULL, NULL);

		if (selectfd == -1)
			throw std::runtime_error("Failed to select the socket");
		else if (selectfd == 0)
			std::cout << "Timeout expired before any file descriptors became ready" << std::endl;
		else
		{
			// Check if the fd with event is the server fd
			// Check if there is activity on the server socket (new connection)
			//The FD_ISSET() macro is used to check if a file descriptor is part of the set of file descriptors passed to the select() call.
			//The accept() call is used to accept the connection request that is recieved on the socket the application was listening to.

			if (FD_ISSET(_serverSocket, &readfds) && acceptClient(&selectfd) == 1)
				continue;

			// Check activity on client sockets

			checkClientActivity(readfds);
		}
	}
}


void Server::clientDisconnect(int clientSocket, size_t &i)
{
	_newfds.erase(_newfds.begin() + i);
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if ((*it)->getFd() == clientSocket)
		{
			_clients.erase(it);
			break;
		}
	}
	close(clientSocket);
	--i; // Adjust index after removal
}
