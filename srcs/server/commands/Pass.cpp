/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:16:23 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/18 15:09:43 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Pass(std::string args, int clientSocket)
{
	int logged = -1;
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
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
			send(clientSocket, constructMessage(ERR_NEEDMOREPARAMS, "PASS").c_str(), 46, 0);
			return;
		}
		if (args[0] == ':')
			args.erase(0, 1);
		if (verifyPassword(args))
			_clients.push_back(new Client(clientSocket));
		else
			send(clientSocket, ERR_PASSWDMISMATCH, 34, 0);
	}
}
