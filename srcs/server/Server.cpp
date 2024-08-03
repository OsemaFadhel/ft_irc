/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:35:39 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/03 19:08:04 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


/* CONSTRUCTOR / DESTRUCTOR ************************************************** */

Server::Server()
{
}

Server::~Server()
{
}


/* GETTERS/SETTERS ****************************************************************** */

void Server::setPort(int port)
{
	_port = port;
}

void Server::setPassword(const std::string& password)
{
	_hashedpassword = hashPassword(password);
}


/* HASH PASSWORD************************************************************* */

bool Server::verifyPassword(const std::string& password) const
{
	return hashPassword(password) == _hashedpassword;
}

std::string Server::hashPassword(const std::string& password) const
{
	unsigned long hash = 5381;
	for (size_t i = 0; i < password.size(); ++i) {
		hash = ((hash << 5) + hash) + password[i]; // hash * 33 + c
	}

	std::ostringstream oss;
	oss << std::hex << hash;
	return oss.str();
}

/* ************************************************************************** */


/* RUN ****************************************************************** */

void Server::run()
{
	while (1)
	{
		// Accept new connections
		// Read from the connections
		// Parse the commands
		// Execute the commands
		// Send the response
	}
}
