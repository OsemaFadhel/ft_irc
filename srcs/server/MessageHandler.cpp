/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:35:50 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/20 17:34:09 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::handleMessage(char* buffer, int readSize ,int clientSocket, size_t &i)
{
	(void)readSize;
	//buffer[readSize - 1] = '\0'; // Null-terminate the buffer
	//handleCarriageReturn(buffer, clientSocket); // Handle the message carriage return
	buffer[readSize] = '\0';
	//buffer[readSize - 1] = '\0';
	if (handleCarriageReturn(buffer, clientSocket, readSize, i) == 1)
		return;
}

int Server::findCarriageReturn(char* buffer, int readSize)
{
	// Check if \r\n is found in the buffer
	for (int i = 0; i < readSize; i++)
	{
		if ((buffer[i] == '\\' && i+1 && buffer[i + 1] == 'r' && buffer[i + 2] == '\n')
				|| (buffer[i] == '\r' && buffer[i + 1] == '\n') || (buffer[i] == '\n'))
			return 1; //found
	}
	return 0; //not found
}

void trimCommand(std::string command)
{
	(void) command;
	//end_last_of('\r''\n');
}

int Server::handleCarriageReturn(char* buffer, int fd, int readSize, size_t &i)
{

	std::cout << YELLOW << "[DEBUG carriage] Handling carriage return" << std::endl;
	std::cout << YELLOW << "[DEBUG carriage 2] Buffer: " << buffer << std::endl;

	// Convert buffer to std::string once
	std::string command;
	command.append(buffer);

	// Keep receiving messages until carriage return is found or buffer size exceeds 512
	while (findCarriageReturn(buffer, readSize) == 0 && command.size() < 512)
	{
		// Receive message
		//std::memset(buffer, 0, sizeof(buffer));
		int bytesRead = recv(fd, buffer, sizeof(buffer), 0);

		//if disconnects
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

		// Append buffer to command
		command.append(buffer, bytesRead);

		// Check if buffer size exceeds 512
		if (command.size() >= 512)
		{
			// Handle buffer overflow
			return 1;
		}
	}
	//trimCommand(command);

	//for tests remove later
	command = command.substr(0, command.length() - 1);

	std::cout << YELLOW << "[DEBUG] Command: " << command << std::endl;
	processCommand(command, fd);


	/*
	if (!carriageReturn)
	{
		std::cout << YELLOW << "[DEBUG] No carriage return found" << std::endl;
		// Append the buffer to the client's buffer
		for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if ((*it)->getFd() == fd)
			{
				(*it)->appendBuffer(buffer, readSize);
				break;
			}
		}
		return 1;
	}

	// Handle the case where \r\n is found in the direct buffer
	std::cout << YELLOW << "[DEBUG] Carriage return found" << std::endl;
	if (carriageReturn)
	{
		int newClientSocket = 0;
		std::cout << YELLOW << "[DEBUG] Carriage return found 2" << std::endl;
		for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if ((*it)->getFd() == fd)
			{
				(*it)->appendBuffer(buffer, readSize);
				std::cout << YELLOW << "[DEBUG] Appended buffer: " << (*it)->getBuffer() << std::endl;
				command = (*it)->getBuffer();
				(*it)->clearBuffer();
				newClientSocket = 1;
				break;
			}
		}
		if (!newClientSocket)
		{
			command = std::string(buffer).substr(0, readSize - 2);
		}
		std::cout << YELLOW << "[DEBUG] Command: " << command << std::endl;
		processCommand(command, fd);
	}*/


	return 0;
}
