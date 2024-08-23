/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:41:13 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/23 19:51:11 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Pong(Client *client, int clientSocket, std::string &message)
{
	(void)client;
	(void)message; //maybe put instead of ServerNAME
	std::string response = "PONG " + SERVERNAME + "\r\n";
	send(clientSocket, response.c_str(), response.length(), 0);
}
