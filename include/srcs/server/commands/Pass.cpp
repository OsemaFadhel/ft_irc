/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:16:23 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/28 16:23:05 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Pass(std::string args, int clientSocket, size_t &i)
{
	int logged = -1;
	for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if ((*it)->getFd() == clientSocket)
		{
			send(clientSocket, ERR_ALREADYREGISTRED, 57, 0);
			logged = 0;
			break;
		}
	}
	if (logged == -1)
	{
		if (args == "")
		{
			std::string message = constructMessage(ERR_NEEDMOREPARAMS, "PASS");
			send(clientSocket, message.c_str(), message.size(), 0);
			return;
		}
		if (args[0] == ':')
			args.erase(0, 1);
		if (verifyPassword(args))
		{
			_clients.push_back(new Client(clientSocket));
			_clients.back()->setHostname(_newfds[i].ip);
		}
		else
			send(clientSocket, ERR_PASSWDMISMATCH, 34, 0);
	}
}
