/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:16:23 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/17 12:18:46 by ofadhel          ###   ########.fr       */
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
				send(clientSocket, ERR_ALREADYREGISTRED(), 55, 0);
				logged = 0;
				break;
			}
		}
		if (logged == -1)
		{
			if (args == "")
			{
				send(clientSocket, ERR_NEEDMOREPARAMS("PASS"), 39, 0);
				return;
			}
			else if (verifyPassword(args))
			{
				_clients.push_back(new Client(clientSocket));
				//send(clientSocket, RPL_WELCOME("ofadhel", "ofadhel_", "irc"), 55 + 14, 0); //CHANGE after nick user
			}
			else
				send(clientSocket, ERR_PASSWDMISMATCH(), 55, 0);
		}
}
