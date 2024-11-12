/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Accept.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:57:35 by ofadhel           #+#    #+#             */
/*   Updated: 2024/11/12 12:10:28 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

int Server::acceptClient()
{
	struct sockaddr_in _clientAddr;
	socklen_t clientAddrSize = sizeof(_clientAddr);
	int clientSocket = accept(_serverSocket, (struct sockaddr*)&_clientAddr, &clientAddrSize);
	if (clientSocket == -1)
	{
		std::cout << RED << "oh NOOO" << RESET << std::endl;
		return 1;
	}

	char *clientIP = inet_ntoa(_clientAddr.sin_addr);  // Non-thread-safe
	if (clientIP == NULL) {
		std::cout << RED << "Failed to retrieve address" << RESET << std::endl;
		close(clientSocket);  // Close the client socket if there's an error
		return -1;
	}

	int clientPort = ntohs(_clientAddr.sin_port);

	socketdata newfd;
	newfd.id = clientSocket;
	newfd.ip = clientIP;
	_newfds.push_back(newfd);

	//_clients.push_back(new Client(clientSocket)); //maybe after recv so can receive password, check and then can add
	std::cout << YELLOW << BOLD << "[DEBUG]" << RESET << YELLOW << " New client accepted. FD is: " << BOLD << clientSocket << " with Address: " << newfd.ip << ":" << clientPort << RESET << std::endl;

	return 0;
}
