/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:39:40 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/04 14:19:00 by lnicoter         ###   ########.fr       */
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

void signalHandler(int signum)
{
	std::cout << "Interrupt signal (" << signum << ") received.\n";
	//killServer();
}

void Server::setMaxfds(int &maxfds, fd_set &readfds)
{
	FD_ZERO(&readfds);
	FD_SET(_serverSocket, &readfds);
	maxfds = _serverSocket;

	for (size_t i = 0; i < _newfds.size(); ++i)
	{
		FD_SET(this->_newfds[i].id, &readfds);
		if (_newfds[i].id > maxfds)
			maxfds = _newfds[i].id;
	}
}

void Server::startLoop(fd_set& readfds, int& maxfds)
{
	signal(SIGINT, signalHandler);

	struct timeval timeout;
	timeout.tv_sec = 180; // 3 minutes
	timeout.tv_usec = 0;

	while (true) // Infinite loop but maybe add flag signal for exit
	{
		setMaxfds(maxfds, readfds);

		int selectfd = select(maxfds + 1, &readfds, NULL, NULL, &timeout);

		if (selectfd == -1)
			throw std::runtime_error("Failed to select file descriptors");
		else if (selectfd == 0)
		{
			std::cout << "Timeout expired before any file descriptors became ready" << std::endl;
			continue;
		}
		else
		{
			if (FD_ISSET(_serverSocket, &readfds) && acceptClient(&selectfd) == 1)
				continue;

			checkClientActivity(readfds);
		}
	}
	//killServer();
}

/*
void Server::killServer()
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		delete *it; // Free each dynamically allocated client
	}
	_clients.clear(); // Clear the vector
	exit(0);
}
*/
