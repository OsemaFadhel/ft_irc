/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandProcess.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:36:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/22 19:00:12 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::processCommand(std::string buffer, int clientSocket)
{
	std::string command = buffer.substr(0, buffer.find(" "));
	std::string args = buffer.length() > command.length() ? buffer.substr(command.length() + 1) : "";
	args.erase(0, args.find_first_not_of(" \t"));

	std::cout << YELLOW << "[DEBUG Command:] " << command << RESET << std::endl;
	std::cout << YELLOW << "[DEBUG Args:] " << args << RESET << std::endl;

	if (getClientIndex(clientSocket) == -1) //not registered (not in _clients, pass not inserted)
	{
		if (command != "PASS" && command != "CAP" && command != "PING")
			return send(clientSocket, ERR_NOTREGISTERED, 39, 0), void();
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
			return send(clientSocket, ERR_NOTREGISTERED, 39, 0), void();
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
		//Join function (Client, Name) here is the next step
	}
}
