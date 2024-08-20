/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientActivity.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:34:51 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/20 17:42:43 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

// Check activity on client sockets
	/*Then we start receiving the data from the client.
	We can specify the required buffer size so that it has enough space
	to receive the data sent the the client. The example of this is shown below.
*/

void Server::checkClientActivity(fd_set& readfds)
{
	//The loop iterates over all the client sockets in the _newfds vector.
	for (size_t i = 0; i < _newfds.size(); ++i)
	{
		int clientSocket = _newfds[i];
		if (FD_ISSET(clientSocket, &readfds))
		{
			char buffer[512];
			std::memset(buffer, 0, sizeof(buffer));
			int readSize = recv(clientSocket, buffer, sizeof(buffer), 0); //maybe implement carriage here.

			/*
			std::string command;
			while ((readsize = recv(clientSocket, buffer, sizeof(buffer), 0)
					&& findCarriageReturn(buffer, readSize) == 0)
			{
				command.append(buffer);
				if (bytesRead <= 0)
				{
					std::cout << RED << "[DEBUG LOOP] Client disconnected. FD = " << fd << std::endl;
					_newfds.erase(_newfds.begin() + i);
					for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
					{
						if ((*it)->getFd() == fd)
						{
							_clients.erase(it);
							break;
						}
					}
					close(fd);
					--i;
					return 1;
				}
				// Check if buffer size exceeds 512
				if (command.size() >= 512)
				{
					// Handle buffer overflow
					return 1;
				}
			}
			command.append(buffer.substr(0, readsize -1));

			*/

			/*DEBUG CARRIAGE REMOVE LATER ************************************ */

			std::cout << YELLOW << "[DEBUG LOOP] readsize:" << readSize << std::endl;
			for (int i = 0; buffer[i]; i++)
			{
				printf("char: %c ", buffer[i]);
				printf("hex: %x ", buffer[i]);
			}
			std::cout << std::endl;

			/************************************************************** */

			if (readSize == -1)
				throw std::runtime_error("Failed to read from the socket");
			else if (readSize == 0)
			{
				std::cout << RED << "[DEBUG LOOP] Client disconnected. FD = " << clientSocket << std::endl;
				clientDisconnect(clientSocket, i);
			}
			else //here starts the handler of the client message. other functions to create
				handleMessage(buffer, readSize, clientSocket, i); // Handle the message
		}
	}
}
