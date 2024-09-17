/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:19:05 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/17 21:35:11 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Nick(std::string args, int clientSocket)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if ((*it)->getFd() == clientSocket)
		{
			if ((*it)->getIsRegistered() < 1)
			{
				if (args == "")
				{
					send(clientSocket, ERR_NONICKNAMEGIVEN, 55, 0);
					return;
				}
				for (std::vector<Client*>::iterator itnick = _clients.begin(); itnick != _clients.end(); ++itnick)
				{
					if ((*itnick)->getNickname() == args)
					{
						std::string message = constructMessage(ERR_NICKNAMEINUSE, (*it)->getNickname());
						send(clientSocket, message.c_str(), 36 + (*it)->getNickname().size(), 0);
						return;
					}
				}
				(*it)->setNickname(args);
				if  ((*it)->getUsername() != "" && (*it)->getIsRegistered() == 0)
				{
					(*it)->setIsRegistered(1);
					std::string message = constructMessage(RPL_WELCOME, (*it)->getNickname(), (*it)->getNickname(), (*it)->getUsername(), "irc");
					send(clientSocket, message.c_str(), 66 + (*it)->getNickname().size() + (*it)->getUsername().size(), 0);
				}
				break;
			}
		}
	}
}

void Server::User(std::string args, int clientSocket) //args = <username> <hostname> <servername> <realname>
{
	if (args == "")
	{
		send(clientSocket, constructMessage(ERR_NEEDMOREPARAMS, "USER").c_str(), 39, 0);
		return;
	}
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if ((*it)->getFd() == clientSocket)
		{
			if ((*it)->getIsRegistered() == 1)
			{
				send(clientSocket, ERR_ALREADYREGISTRED, 44, 0);
				return;
			}

			(*it)->setUsername(args);

			if  ((*it)->getNickname() != "")
			{
				(*it)->setIsRegistered(1);
				std::string message = constructMessage(RPL_WELCOME, (*it)->getNickname(), (*it)->getNickname(), (*it)->getUsername(), "irc");
				send(clientSocket, message.c_str(), 66 + (*it)->getNickname().size() + (*it)->getUsername().size(), 0);
			}
			break;
		}
	}
}
