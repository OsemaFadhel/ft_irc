/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:35:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/09 15:49:17 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>   // For strerror
#include <cstdio>
#include <sstream>
#include <vector>
#include <map>
#include <fcntl.h>
#include <openssl/sha.h>
#include <poll.h>
#include <string>
#include <netinet/in.h>
#include <fstream>
#include <sys/socket.h>
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"

class Client;
class Channel;

class Server
{
	private:
		int _port;
		int _serverSocket; //tcp
		std::string _password;
		std::vector < Client* > _clients;
		std::vector < Channel* > _channels;
		std::string hashPassword(const std::string& password) const;
		struct sockaddr_in _serverAddr;

		//std::map < std::string, *Cmd > Commands; //to fix
	public:
		Server();
		~Server();
		void setPort(int port);
		void setPassword(const std::string& password);
		bool verifyPassword(const std::string& password) const;
		void run();
		void acceptClient(int fd);
};

#endif
