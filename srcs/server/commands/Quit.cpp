/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:08:31 by ofadhel           #+#    #+#             */
/*   Updated: 2024/11/12 11:57:07 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Quit(std::string args, int clientSocket, size_t &i)
{
	(void)args;

	_newfds.erase(_newfds.begin() + i);

	Client *client = getClient(clientSocket);
	if (client)
	{
		std::cout << RED << "[DEBUG QUIT] Client disconnected. Nickname: " << client->getNickname() << RESET << std::endl;
		// Remove the client from all channels
		for (size_t i = 0; i < _channels.size(); ++i)
		{
			if (_channels[i].isInChannel(*client))
				_channels[i].removeClient(*client);
		}
		deleteEmptyChannels();
		removeClient(clientSocket);
	}

	close(clientSocket);
	--i;
}
