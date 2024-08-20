/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandProcess.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:36:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/20 14:54:56 by ofadhel          ###   ########.fr       */
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
			}
			else
			if (verifyPassword(data))
			{
				//send(clientSocket, ":ft_irc :Password correct. You're now logged in\n", 55, 0);
				_clients.push_back(new Client(clientSocket));
				send(clientSocket, RPL_WELCOME("ofadhel", "ofadhel_", "irc"), 55 + 14, 0); //CHANGE
			}
			/*else
				send(clientSocket, ":ft_irc :Password incorrect\n", 39, 0);*/
		}
	}
	else
	{
		// Handle other commands
	}
}
