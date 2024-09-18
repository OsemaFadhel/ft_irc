/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:35:50 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/18 15:15:19 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::trimCommand(std::string &command)
{
	// Trim the command
	command.erase(command.find_last_not_of(" \n\r\t") + 1);
	command.erase(0, command.find_first_not_of(" \n\r\t"));
}

std::vector<std::string> Server::splitCommand(std::string &command)
{
	std::vector<std::string> vector;
	std::string delimiter = "\r\n";
	size_t pos = 0;
	std::string token;

	while ((pos = command.find(delimiter)) != std::string::npos)
	{
		token = command.substr(0, pos);
		vector.push_back(token);
		command.erase(0, pos + delimiter.length());
	}
	return vector;
}

void Server::handleMessage(std::string buffer, int readSize, int clientSocket)
{
	(void)readSize;
	(void)clientSocket;

	std::vector<std::string> vector = splitCommand(buffer);

	for (size_t i = 0; i < vector.size(); i++)
		processCommand(vector[i], clientSocket);
}

int Server::findCarriageReturn(char* buffer, int readSize)
{
	for (int i = readSize - 1; i >= 0; i--)
	{
		if ((buffer[i] == '\n' && i - 1 > 0 && buffer[i - 1] == 'r' && buffer[i - 2] == '\\')
			|| (buffer[i] == '\n' && i - 1 < readSize && buffer[i - 1] == '\r'))
			return i;
	}
	return 0; //not found
}
