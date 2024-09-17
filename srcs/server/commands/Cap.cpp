/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CapLs.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:41:15 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/17 18:37:21 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Cap(int clientSocket)
{
	std::string cap = ":" + SERVERNAME + " CAP * LS \r\n"; //if not logged
	std::string response = ":" + SERVERNAME + " CAP " + getClient(clientSocket)->getNickname() + " LS :\r\n";
	send(clientSocket, response.c_str(), response.length(), 0);
}
