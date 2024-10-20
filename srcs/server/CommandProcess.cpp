/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandProcess.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:36:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/20 18:47:02 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::processCommand(std::string buffer, int clientSocket, size_t &i)
{
	std::cout << CYAN << "[DEBUG] Processing command: " << buffer << RESET << std::endl;

	std::string command = buffer.substr(0, buffer.find(" "));
	std::string args = buffer.length() > command.length() ? buffer.substr(command.length() + 1) : "";
	args.erase(0, args.find_first_not_of(" \t"));

	// Get client details
	int clientIndex = getClientIndex(clientSocket);
	Client* client = getClient(clientSocket); //remove
	bool isRegistered = client && client->getIsRegistered();

	if (clientIndex == -1) //not registered (not in _clients, pass not inserted)
	{
		if (command != "PASS" && command != "CAP" && command != "PING" && command != "QUIT")
			return send(clientSocket, ERR_NOTREGISTERED, 39, 0), void();

		if (command == "PASS")
			Pass(args, clientSocket);
		else if (command == "PING")
			Ping(client, clientSocket, args);
		else if (command == "CAP")
			Cap(clientSocket);
		else if (command == "QUIT")
			Quit(args, clientSocket, i);
	}
	else if (!isRegistered)
	{
		if (command != "NICK" && command != "USER" && command != "PING" && command != "CAP" && command != "PASS" && command != "QUIT")
			return send(clientSocket, ERR_NOTREGISTERED, 39, 0), void();

		if (command == "NICK")
			Nick(args, clientSocket);
		else if (command == "USER")
			User(args, clientSocket);
		else if (command == "PASS")
			Pass(args, clientSocket);
		else if (command == "PING")
			Ping(client, clientSocket, args);
		else if (command == "CAP")
			Cap(clientSocket);
		else if (command == "QUIT")
			Quit(args, clientSocket, i);
	}
	// Handle fully registered clients
	else
	{
		if (command == "PASS")
			Pass(args, clientSocket);
		else if (command == "NICK")
			Nick(args, clientSocket);
		else if (command == "USER")
			User(args, clientSocket);
		else if (command == "PING")
			Ping(client, clientSocket, args);
		else if (command == "CAP")
			Cap(clientSocket);
		else if (command == "QUIT")
			Quit(args, clientSocket, i);
		else if (command == "JOIN")
			Join(args, clientSocket);
		else if (command == "PRIVMSG")
			Privmsg(args, clientSocket);
		else if (command == "TOPIC")
			Topic(args, client);
	}
}
