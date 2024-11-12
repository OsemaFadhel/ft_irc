/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientActivity.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:34:51 by ofadhel           #+#    #+#             */
/*   Updated: 2024/11/12 12:12:45 by ofadhel          ###   ########.fr       */
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
		int clientSocket = _newfds[i].id;

		if (FD_ISSET(clientSocket, &readfds))
		{
			char buffer[1024];
			int readSize = 0;
			std::string command;

			std::memset(buffer, 0, sizeof(buffer)); // Clear the buffer
			readSize = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

			if (readSize < 0)
			{
				std::cout << RED << "[DEBUG LOOP] Failed to read from the socket. FD = " << clientSocket << std::endl;
				break;
			}
			if (readSize == 0) {
				std::cout << YELLOW << BOLD << "[QUIT 1]" << RESET << YELLOW << " Client disconnected. FD = " << clientSocket << std::endl;
				clientDisconnect(clientSocket, i);
				break;
			}

			this->_newfds[i].buffer.append(buffer);
			if (this->_newfds[i].buffer.size() >= 512) {
				std::cout << RED << "[DEBUG LOOP] Message size too big. FD = " << clientSocket << std::endl;
				this->_newfds[i].buffer.clear();
				break; // Handle buffer overflow scenario
			}
			if (findCarriageReturn(buffer, readSize) != 0) // Check if carriage return is found
			{
				handleMessage(this->_newfds[i].buffer, this->_newfds[i].buffer.length(), clientSocket, i); // Handle the message
				break; // Exit the loop once the full command is received
			}
			else if (this->_newfds[i].buffer.find("\n") != std::string::npos) // Check if only \n is found remove it so it doesn't get appended to the buffer
			{
				//remove the \n from the buffer
				this->_newfds[i].buffer.erase(this->_newfds[i].buffer.find("\n"));
				break; // Handle buffer overflow scenario
			}
			// Check if the command length exceeds 512
		}
	}
}

void Server::clientDisconnect(int clientSocket, size_t &i)
{
	_newfds.erase(_newfds.begin() + i);
	Client *client = getClient(clientSocket);
	if (client)
	{
		std::cout << RED << "[QUIT 2] Client disconnected. Nickname: " << client->getNickname() << " FD = " << clientSocket << std::endl;
		// Remove the client from all channels
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			if (_channels[i].isInChannel(*client))
				_channels[i].removeClient(*client);
		}
		deleteEmptyChannels();
		// Remove the client from the clients vector
		removeClient(clientSocket);
	}
	close(clientSocket);
	--i; // Adjust index after removal
}
