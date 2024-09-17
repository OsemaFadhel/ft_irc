/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:19:05 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/17 12:22:03 by ofadhel          ###   ########.fr       */
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
							send(clientSocket, ERR_NICKNAMEINUSE("nick"), 55 + args.size(), 0);
							return;
						}
					}
					(*it)->setNickname(args);\
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

void Server::User(std::string args, int clientSocket)
{
	if (args == "")
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
			(*it)->setUsername(args);
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
