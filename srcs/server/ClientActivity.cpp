/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientActivity.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:34:51 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/19 17:41:06 by lnicoter         ###   ########.fr       */
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

			while (1) //think i can remove this loop
			{
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

				this->_newfds[i].buffer.append(buffer);
				if (findCarriageReturn(buffer, readSize) != 0) // Check if carriage return is found
				{
					handleMessage(this->_newfds[i].buffer, this->_newfds[i].buffer.length(), clientSocket); // Handle the message
					this->_newfds[i].buffer.erase(); // Clear the buffer
					break; // Exit the loop once the full command is received
				}
				else if (this->_newfds[i].buffer.find("\n") != std::string::npos) // Check if only \n is found remove it so it doesn't get appended to the buffer
				{
					//remove the \n from the buffer
					this->_newfds[i].buffer.erase(this->_newfds[i].buffer.find("\n"));
					break; // Handle buffer overflow scenario
				}
				// Check if the command length exceeds 512
				if (this->_newfds[i].buffer.size() >= 512) {
					std::cout << RED << "[DEBUG LOOP] Buffer overflow. FD = " << clientSocket << std::endl;
					break; // Handle buffer overflow scenario
				}
				break;
			}
		}
	}
}
