/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:39:40 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/23 22:07:18 by lnicoter         ###   ########.fr       */
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
		FD_SET(this->_newfds[i].id, &readfds);
		if (_newfds[i].id > maxfds)
			maxfds = _newfds[i].id;
	}
}

void Server::startLoop(fd_set& readfds, int& maxfds)
{
	while (1)
	{
		setMaxfds(maxfds, readfds);

		int selectfd = select(maxfds + 1, &readfds, NULL, NULL, NULL);

		if (selectfd == -1)
			throw std::runtime_error("Failed to select the socket");
		else if (selectfd == 0)
			std::cout << "Timeout expired before any file descriptors became ready" << std::endl;
		else
		{
			if (FD_ISSET(_serverSocket, &readfds) && acceptClient(&selectfd) == 1)
				continue;

			checkClientActivity(readfds);
		}
	}
}

