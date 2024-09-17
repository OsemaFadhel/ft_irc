/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandProcess.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:36:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/17 12:23:26 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::processCommand(std::string buffer, int clientSocket)
{
	std::string command = buffer.substr(0, buffer.find(" "));
	std::string args = buffer.substr(buffer.find(" ") + 1);

	//check if client is registered
	//if not registered, only pass, nick and user are allowed
	//if registered, all commands are allowed

	if (command == "PASS")
		Pass(args, clientSocket);
	else if (command == "NICK")
		Nick(args, clientSocket);
	else if (command == "USER")
		User(args, clientSocket);
	// else
		//Nicotera(cmd, args, clientSocket);
}
