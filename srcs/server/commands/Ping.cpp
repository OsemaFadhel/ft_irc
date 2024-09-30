/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:41:13 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/30 13:43:55 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Ping(Client* client, int clientSocket, std::string &message)
{
	(void)client;
	(void)message; //maybe put instead of ServerNAME
	std::string response = "PONG " + SERVERNAME + "\r\n";
	send(clientSocket, response.c_str(), response.length(), 0);
}
