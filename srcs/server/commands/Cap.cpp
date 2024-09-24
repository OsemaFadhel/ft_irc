/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:41:15 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/24 14:19:46 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Cap(int clientSocket)
{
	if (getClient(clientSocket).getIsRegistered() == 1) //if logged in
	{
		std::string response = ":" + SERVERNAME + " CAP " + getClient(clientSocket).getNickname() + " LS :\r\n";
		send(clientSocket, response.c_str(), response.length(), 0);
		return;
	}
	else
	{
		std::string response = ":" + SERVERNAME + " CAP * LS \r\n"; //if not logged in
		send(clientSocket, response.c_str(), response.length(), 0);
	}
}
