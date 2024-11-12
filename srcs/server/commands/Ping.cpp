/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:41:13 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/04 12:19:07 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Ping(Client *client, int clientSocket, std::string &message)
{
	std::istringstream iss(message);
	std::string first, second;

	iss >> first;

	if (client == NULL)
	{
		std::string response = "PONG " + SERVERNAME + "\r\n";
		send(clientSocket, response.c_str(), response.length(), 0);
		return;
	}

	iss >> second;

	if (second.empty())
	{
		std::string response = "PONG " + SERVERNAME + "\r\n";
		send(clientSocket, response.c_str(), response.length(), 0);
		return;
	}

	std::string response = "PONG " + SERVERNAME + " " + first + "\r\n";
	send(clientSocket, response.c_str(), response.length(), 0);
}
