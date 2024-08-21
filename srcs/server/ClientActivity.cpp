/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientActivity.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:34:51 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/21 16:08:44 by ofadhel          ###   ########.fr       */
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
			char buffer[1024];
			int readSize = 0;
			std::string command;

			while (1) {
				std::memset(buffer, 0, sizeof(buffer)); // Clear the buffer
				readSize = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

				if (readSize < 0) {
					throw std::runtime_error("Failed to read from the socket");
				}
				if (readSize == 0) {
					std::cout << RED << "[DEBUG LOOP] Client disconnected. FD = " << clientSocket << std::endl;
					clientDisconnect(clientSocket, i);
					break;
				}

				buffer[readSize] = '\0'; // Null-terminate the received data

				command.append(buffer, readSize); // Append the received data to the command string

				if (findCarriageReturn(buffer, readSize) != 0) { // Check if carriage return is found
					break; // Exit the loop once the full command is received
				}

				// Check if the command length exceeds 512
				if (command.size() >= 512) {
					std::cout << RED << "[DEBUG LOOP] Buffer overflow. FD = " << clientSocket << std::endl;
					break; // Handle buffer overflow scenario
				}
			}

			/*readSize = recv(clientSocket, buffer, sizeof(buffer), 0);
			if (findCarriageReturn(buffer,readSize) == 0)
			{
				while ((recv(clientSocket, buffer, sizeof(buffer), 0)
						&& findCarriageReturn(buffer, std::string(buffer).length()) == 0))
				{
					command.append(buffer);
					std::memset(buffer, 0, sizeof(buffer));
					if (readSize == -1)
					throw std::runtime_error("Failed to read from the socket");
					if (readSize == 0)
					{
						std::cout << RED << "[DEBUG LOOP] Client disconnected. FD = " << clientSocket << std::endl;
						clientDisconnect(clientSocket, i);
						break;
					}
					// Check if buffer size exceeds 512
					if (command.size() >= 512)
					{
						// Handle buffer overflow
						std::cout << RED << "[DEBUG LOOP] Buffer overflow. FD = " << clientSocket << std::endl;
						break;
					}
				}
			}
			command.append(buffer);*/

			/*DEBUG CARRIAGE REMOVE LATER ************************************

			std::cout << YELLOW << "[DEBUG LOOP] readsize:" << readSize << std::endl;
			for (int i = 0; buffer[i]; i++)
			{
				printf("char: %c ", buffer[i]);
				printf("hex: %x ", buffer[i]);
			}
			std::cout << std::endl;

			************************************************************** */

			/*if (readSize == -1)
				throw std::runtime_error("Failed to read from the socket");
			else if (readSize == 0)
			{
				std::cout << RED << "[DEBUG LOOP 2] Client disconnected. FD = " << clientSocket << std::endl;
				clientDisconnect(clientSocket, i);
			}*/
			if (!command.empty()) //here starts the handler of the client message. other functions to create
				handleMessage(command, command.length(), clientSocket); // Handle the message
		}
	}
}
