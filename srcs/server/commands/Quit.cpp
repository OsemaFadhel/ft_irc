/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:08:31 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/24 14:18:32 by lnicoter         ###   ########.fr       */
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
	Client client = getClient(clientSocket);
	//std::string message = constructMessage(RPL_QUIT, client->getNickname().c_str(), args.c_str());
	//send(clientSocket, message.c_str(), message.size(), 0);
	//broadcast(clientSocket, message);
	_clients.erase(_clients.begin() + getClientIndex(clientSocket));

	close(clientSocket);
}
