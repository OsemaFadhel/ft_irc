/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:41:15 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/18 14:43:29 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Cap(int clientSocket)
{
	if (getClient(clientSocket) && getClient(clientSocket)->getIsRegistered() == 1) //if logged in
	{
		std::string response = ":" + SERVERNAME + " CAP " + getClient(clientSocket)->getNickname() + " LS :\r\n";
		send(clientSocket, response.c_str(), response.length(), 0);
		return;
	}
	else
	{
		std::string response = ":" + SERVERNAME + " CAP * LS \r\n"; //if not logged in
		send(clientSocket, response.c_str(), response.length(), 0);
	}
}
