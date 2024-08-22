/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:35:50 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/22 15:39:55 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::trimCommand(std::string &command)
{
	// Trim the command
	command.erase(command.find_last_not_of(" \n\r\t") + 1);
}

void Server::handleMessage(std::string buffer, int readSize ,int clientSocket)
{
	(void)readSize;
	std::cout << YELLOW << "[DEBUG] Command: " << buffer << std::endl;
	for (int i = 0; buffer[i]; i++)
	{
		printf("char: %c ", buffer[i]);
		printf("hex: %x ", buffer[i]);
		std::cout << std::endl;
	}
	std::cout << std::endl;
	trimCommand(buffer);
	/*maybe put while loop like
	split messsage and fill a list o other container
	vector = split(buffer) \r\n
	for (vector it++)
	{
		processCommand(vector[i], clientSocket);
	}*/
	//processCommand(buffer, clientSocket); // now here splits the command everytime it finds a \r\n inside, and then process it in order.
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
