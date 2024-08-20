/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Accept.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:57:35 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/20 14:57:49 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

int Server::acceptClient(int *selectfd)
{
	struct sockaddr_in _clientAddr;
	socklen_t clientAddrSize = sizeof(_clientAddr);
	int clientSocket = accept(_serverSocket, (struct sockaddr*)&_clientAddr, &clientAddrSize);
	if (clientSocket == -1)
		throw std::runtime_error("Failed to accept the connection");

	_newfds.push_back(clientSocket);
	//_clients.push_back(new Client(clientSocket)); //maybe after recv so can receive password, check and then can add
	std::cout << GREEN << "[DEBUG] New client accepted. FD is: " << BOLD << clientSocket << std::endl;
	selectfd--;
	if (!selectfd)
		return 1;
	return 0;
}
