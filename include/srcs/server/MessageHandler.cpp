/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:35:50 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/04 12:35:22 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::trimCommand(std::string &command)
{
	// Trim the command
	command.erase(command.find_last_not_of(" \n\r\t") + 1);
	command.erase(0, command.find_first_not_of(" \n\r\t"));
}

std::vector<std::string> Server::splitCommand(std::string command)
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

void Server::handleMessage(std::string buffer, int readSize, int clientSocket, size_t &i)
{
	(void)readSize;
	(void)clientSocket;

	std::vector<std::string> vector = splitCommand(buffer);
	this->_newfds[i].buffer.clear();

	for (size_t j = 0; j < vector.size(); j++)
		processCommand(vector[j], clientSocket, i);
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
