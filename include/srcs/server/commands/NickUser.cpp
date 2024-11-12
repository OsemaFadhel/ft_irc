/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickUser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:19:05 by ofadhel           #+#    #+#             */
/*   Updated: 2024/11/12 11:54:31 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

bool isSpecial(char c)
{
	return (c == '[' || c == ']' || c == '\\' || c == '^' ||
			c == '{' || c == '}' || c == '|');
}

int checkNickvalidity(std::string args, int clientSocket)
{
	std::string messageErr = constructMessage(ERR_ERRONEUSNICKNAME, "NICK");
	if (args.find_first_of(" \t") != std::string::npos) //if there is a space or tab
		return send(clientSocket, messageErr.c_str(), messageErr.size(), 0), -1;

	if (args == "") //if the nickname is empty
		return send(clientSocket, ERR_NONICKNAMEGIVEN, 33, 0), -1;

	if (args.size() > 9) //if the nickname is too long or empty
		return send(clientSocket, messageErr.c_str(), messageErr.size(), 0), -1;

	char first = args[0];
	if (!std::isalpha(first) && !isSpecial(first)) //if the first character is not a letter or a special character
		return send(clientSocket, messageErr.c_str(), messageErr.size(), 0), -1;

	for (size_t i = 1; i < args.length(); ++i)
	{
		char c = args[i];
		if (!std::isalnum(c) && !isSpecial(c) && c != '-') //if the character is not alphanumeric, special or a dash
		return send(clientSocket, messageErr.c_str(), messageErr.size(), 0), -1;
	}

	return 0;
}

void Server::Nick(std::string args, int clientSocket)
{
	args.erase(args.find_last_not_of(" \t") + 1);

	if (checkNickvalidity(args, clientSocket) == -1)
		return;


	Client *client = getClient(clientSocket);

	for (std::vector<Client * >::iterator itnick = _clients.begin(); itnick != _clients.end(); ++itnick) //check if the nickname is already in use
	{
		if ((*itnick)->getNickname() == args)
		{
			std::string message = constructMessage(ERR_NICKNAMEINUSE, args.c_str());
			send(clientSocket, message.c_str(), message.size(), 0);
			return;
		}
	}

	std::string messageToSend = ":" + client->getNickname() + " NICK " + args + "\r\n";

	//MAYbe add broadcast to all channels
	for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->isInChannel(*client) != -1)
		{
			std::vector<std::pair<Client, int> >	usrData = it->getUsrData();

			for (size_t i = 0; i < usrData.size(); i++)
			{
				if (usrData[i].first.getFd() != client->getFd())
					send(usrData[i].first.getFd(), messageToSend.c_str(), messageToSend.size(), 0);
			}
		}
	}

	client->setNickname(args);

	if  (client->getUsername() != "" && client->getIsRegistered() == 0)
	{
		client->setIsRegistered(1);
		std::string message = constructMessage(RPL_WELCOME, client->getNickname().c_str(),
			SERVERNAME.c_str(), client->getNickname().c_str());
		std::cout << GREEN << "[NEW USER] " << message << RESET << std::endl;
		send(clientSocket, message.c_str(), message.size(), 0);
	}
}


void Server::User(std::string args, int clientSocket) //args = <username> <hostname> <servername> <realname>
{
	if (args == "")
	{
		send(clientSocket, constructMessage(ERR_NEEDMOREPARAMS, "USER").c_str(), 45, 0);
		return;
	}
	args.erase(args.find_last_not_of(" \t") + 1);

	Client *client = getClient(clientSocket);

	if (client->getIsRegistered() == 1)
		return send(clientSocket, ERR_ALREADYREGISTRED, 57, 0), void();

	// Parsing the USER command arguments
	std::istringstream iss(args);
	std::string username, mode, unused, realname;

	// Extract username, mode, unused, and realname from the args string
	if (!(iss >> username >> mode >> unused))
		return send(clientSocket, constructMessage(ERR_NEEDMOREPARAMS, "USER").c_str(), 39, 0), void();

	// Extract the realname (may contain spaces) - everything after the ':'
	std::getline(iss, realname);
	// Remove leading and trailing whitespaces
	realname.erase(realname.find_last_not_of(" \t") + 1);
	realname.erase(0, realname.find_first_not_of(" \t"));
	if (realname.empty() || realname[0] != ':')
		return send(clientSocket, constructMessage(ERR_NEEDMOREPARAMS, "USER").c_str(), 39, 0), void();

	// Remove the leading ':' from the realname
	realname = realname.substr(1);

	size_t pos = realname.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	if (pos != std::string::npos)
		realname = realname.substr(pos); // Trim everything before the realname

	// Set the username and realname in the client object
	client->setUsername(username);
	client->setRealName(realname);

	if  (client->getNickname() != "")
	{
		client->setIsRegistered(1);
		std::string message = constructMessage(RPL_WELCOME, client->getNickname().c_str(),
			SERVERNAME.c_str(), client->getNickname().c_str());
		std::cout << GREEN << "[NEW USER] " << message << RESET << std::endl;
		send(clientSocket, message.c_str(), message.length(), 0);
	}
}
