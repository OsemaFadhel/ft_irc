/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandProcess.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:36:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/29 16:02:32 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::processCommand(std::string buffer, int clientSocket)
{
	std::string command(buffer); // Example command handling
	std::string data; // Parse data from command as needed

	if (command.substr(0, 4) == "PASS")
	{
		int logged = -1;
		for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if ((*it)->getFd() == clientSocket)
			{
				send(clientSocket, ERR_ALREADYREGISTRED(), 55, 0);
				logged = 0;
				break;
			}
		}
		if (logged == -1)
		{
			data = command.substr(5);
			if (data == "")
			{
				send(clientSocket, ERR_NEEDMOREPARAMS("PASS"), 39, 0);
				return;
			}
			else if (verifyPassword(data))
			{
				_clients.push_back(new Client(clientSocket));
				//send(clientSocket, RPL_WELCOME("ofadhel", "ofadhel_", "irc"), 55 + 14, 0); //CHANGE after nick user
			}
			else
				send(clientSocket, ERR_PASSWDMISMATCH(), 55, 0);
		}
	}
	else if (command.substr(0, 4) == "NICK")
	{
		for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if ((*it)->getFd() == clientSocket)
			{
				if ((*it)->getIsRegistered() < 1)
				{
					data = command.substr(5);
					if (data == "")
					{
						send(clientSocket, ERR_NONICKNAMEGIVEN, 55, 0);
						return;
					}
					for (std::vector<Client*>::iterator itnick = _clients.begin(); itnick != _clients.end(); ++itnick)
					{
						if ((*itnick)->getNickname() == data)
						{
							send(clientSocket, ERR_NICKNAMEINUSE("nick"), 55 + data.size(), 0);
							return;
						}
					}
					(*it)->setNickname(data);\
					if  ((*it)->getUsername() != "")
					{
						(*it)->setIsRegistered(1);
						//send(clientSocket, RPL_WELCOME((*it)->getNickname(), (*it)->getUsername(), "irc"), 55 + (*it)->getNickname().size() + (*it)->getUsername().size(), 0);
					}
					break;
				}
				else
				{
					send(clientSocket, ERR_ALREADYREGISTRED(), 55, 0);
					return;
				}
			}
		}
		//else (no pass inserted)
	}
	else if (command.substr(0, 4) == "USER")
	{
		data = command.substr(5);
		if (data == "")
		{
			send(clientSocket, ERR_NEEDMOREPARAMS("USER"), 39, 0);
			return;
		}
		for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if ((*it)->getFd() == clientSocket)
			{
				if ((*it)->getIsRegistered() == 1)
				{
					send(clientSocket, ERR_ALREADYREGISTRED(), 55, 0);
					return;
				}
				(*it)->setUsername(data);
				//send(clientSocket, RPL_WELCOME((*it)->getNickname(), (*it)->getUsername(), "irc"), 55 + (*it)->getNickname().size() + (*it)->getUsername().size(), 0);
				break;
			}
			if  ((*it)->getNickname() != "")
			{
				(*it)->setIsRegistered(1);
				//send(clientSocket, RPL_WELCOME((*it)->getNickname(), (*it)->getUsername(), "irc"), 55 + (*it)->getNickname().size() + (*it)->getUsername().size(), 0);
			}
		}
	}
	else
	{
	}
}
