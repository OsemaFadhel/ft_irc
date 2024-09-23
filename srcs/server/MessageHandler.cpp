/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:35:50 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/22 18:59:04 by lnicoter         ###   ########.fr       */
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
	//why the commands are messed up???? let's discover why in the future
	while ((pos = command.find(delimiter)) != std::string::npos)
	{
		token = command.substr(0, pos);
		vector.push_back(token);
		command.erase(0, pos + delimiter.length());
	}
	for (int i = 0; i < (int)vector.size(); i++)
		std::cout<<"read values in splitcmd "<<vector[i]<<std::endl;
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
