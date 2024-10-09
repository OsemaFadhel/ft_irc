/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:43:18 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/09 14:45:26 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Client.hpp"

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
		std::string port = av[1];
		Server server;
		server.setPort(std::atoi(port.c_str()));
		if (server.getPort() < 1024 || server.getPort() > 65535)
			throw std::runtime_error("Invalid port number");
		server.setPassword(av[2]);
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		//killServer();
		return 1;
	}
	return 0;
}
