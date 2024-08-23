/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:35:50 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/23 18:47:35 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::trimCommand(std::string &command)
{
	// Trim the command
	command.erase(command.find_last_not_of(" \n\r\t \\r") + 1);
}

void Server::handleMessage(std::string buffer, int readSize, int clientSocket)
{
	(void)readSize;
	(void)clientSocket;
	std::cout << YELLOW << "[DEBUG] Command: " << buffer << std::endl;

	printf("char: %c ", buffer[readSize - 1]);
	printf("hex: %x ", buffer[readSize - 1]);
	printf("dec: %d ", buffer[readSize - 2]);
	printf("char: %c ", buffer[readSize - 2]);
	std::cout << std::endl;
	trimCommand(buffer);
	std::cout << "buffer after trim: " << buffer << std::endl;
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
	/*
	for (int i = 0; i < readSize; i++)
	{
		if ((buffer[i] == '\\' && i + 1 && buffer[i + 1] == 'r' && i + 2 && buffer[i + 2] == '\n')
				|| (buffer[i] == '\r' && i + 1 && buffer[i + 1] == '\n'))
			return i;
	}
	*/
	for (int i = readSize - 1; i >= 0; i--)
    {
        if ((buffer[i] == '\n' && i - 1 > 0 && buffer[i - 1] == 'r' && buffer[i - 2] == '\\')
            || (buffer[i] == '\n' && i - 1 < readSize && buffer[i - 1] == '\r'))
            return i;
    }
	return 0; //not found
}
