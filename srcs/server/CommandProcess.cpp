/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandProcess.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:36:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/04 14:18:43 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::processCommand(std::string buffer, int clientSocket, size_t &i)
{
	std::string command = buffer.substr(0, buffer.find(" "));
	std::string args = buffer.length() > command.length() ? buffer.substr(command.length() + 1) : "";
	args.erase(0, args.find_first_not_of(" \t"));

	std::cout << YELLOW << "[DEBUG Command:] " << command << RESET << std::endl;
	std::cout << YELLOW << "[DEBUG Args:] " << args << RESET << std::endl;

	if (getClientIndex(clientSocket) == -1) //not registered (not in _clients, pass not inserted)
	{
		if (command != "PASS" && command != "CAP" && command != "PING" && command != "QUIT"
			&& command != "JOIN")
			return send(clientSocket, ERR_NOTREGISTERED, 39, 0), void();
		else if (command == "PASS")
			Pass(args, clientSocket);
		else if (command == "PING")
			Ping(getClient(clientSocket), clientSocket, args);
		else if (command == "CAP")
			Cap(clientSocket);
		else if (command == "QUIT")
			Quit(args, clientSocket, i);
	}
	else if (getClientIndex(clientSocket) != -1 && getClient(clientSocket)->getIsRegistered() == 0) //registered (in _clients, pass inserted)
	{
		if (command != "NICK" && command != "USER" && command != "PING" && command != "CAP" && command != "PASS"
			&& command != "QUIT" && command != "JOIN")
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
		else if (command == "QUIT")
			Quit(args, clientSocket, i);
	}
	else if (getClientIndex(clientSocket) != -1 && getClient(clientSocket)->getIsRegistered() == 1)
	{
		if (command == "PASS")
			Pass(args, clientSocket);
		else if (command == "NICK")
			Nick(args, clientSocket);
		else if (command == "USER")
			User(args, clientSocket);
		else if (command == "PING")
			Ping(getClient(clientSocket), clientSocket, args);
		else if (command == "CAP")
			Cap(clientSocket);
		else if (command == "QUIT")
			Quit(args, clientSocket, i);
		else if (command == "JOIN")
			Join(args, clientSocket);
		else if (command == "PRIVMSG")
			Privmsg(args, clientSocket);
	}
}
