/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:43:18 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/03 18:53:30 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"
#include "client/Client.hpp"

int main(int ac, char **av)
{
	// Check for the right number of arguments
	if (ac != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	// Try to run the server
	try
	{
		std::string password = av[2];
		std::string port = av[1];
		Server server;
		server.setPort(std::atoi(port.c_str()));
		server.setPassword(av[2]);
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
