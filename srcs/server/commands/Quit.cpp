/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:08:31 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/04 12:05:49 by ofadhel          ###   ########.fr       */
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
		removeClient(clientSocket);
	}

	close(clientSocket);
	--i;
}
