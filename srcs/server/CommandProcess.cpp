/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandProcess.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:36:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/17 21:21:49 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::processCommand(std::string buffer, int clientSocket)
{
	std::string command = buffer.substr(0, buffer.find(" "));
	std::string args = buffer.substr(buffer.find(" ") + 1);

	if (getClientIndex(clientSocket) == -1) //not registered (not in _clients, pass not inserted)
	{
		if (command != "PASS" && command != "CAP" && command != "PING")
			return send(clientSocket, ERR_NOTREGISTERED, 55, 0), void();
		else if (command == "PASS")
			Pass(args, clientSocket);
		else if (command == "PING")
			Ping(getClient(clientSocket), clientSocket, args);
		else if (command == "CAP")
			Cap(clientSocket);
	}
	else if (getClientIndex(clientSocket) != -1 && getClient(clientSocket)->getIsRegistered() == 0) //registered (in _clients, pass inserted)
	{
		if (command != "NICK" && command != "USER" && command != "PING" && command != "CAP" && command != "PASS")
			return send(clientSocket, ERR_NOTREGISTERED, 55, 0), void();
		else if (command == "NICK")
			Nick(args, clientSocket);
		else if (command == "USER")
			User(args, clientSocket);
		else if (command == "PASS")
			Pass(args, clientSocket);
		else if (command == "PING")
			Ping(getClient(clientSocket), clientSocket, args);
		else if (command == "CAP")
			Cap(clientSocket);
	}
	else if (getClientIndex(clientSocket) != -1 && getClient(clientSocket)->getIsRegistered() == 1)
	{
		if (command == "Pass")
			Pass(args, clientSocket);
		else if (command == "NICK")
			Nick(args, clientSocket);
		else if (command == "USER")
			User(args, clientSocket);
		else if (command == "PING")
			Ping(getClient(clientSocket), clientSocket, args);
		else if (command == "CAP")
			Cap(clientSocket);
		//Nicotera(cmd, args, clientSocket);
	}
}
