/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:08:31 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/19 15:23:39 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Quit(std::string args, int clientSocket)
{
	(void)args;
	for (size_t i = 0; i < _newfds.size(); ++i)
	{
		if (_newfds[i].id == clientSocket)
		{
			std::cout << RED << "[DEBUG] Client disconnected. FD: " << _newfds[i].id << std::endl;
			_newfds.erase(_newfds.begin() + i);
			break;
		}
	}
	Client *client = getClient(clientSocket);
	if (client)
	{
		//std::string message = constructMessage(RPL_QUIT, client->getNickname().c_str(), args.c_str());
		//send(clientSocket, message.c_str(), message.size(), 0);
		//broadcast(clientSocket, message);
		_clients.erase(_clients.begin() + getClientIndex(clientSocket));
	}
	close(clientSocket);
}
