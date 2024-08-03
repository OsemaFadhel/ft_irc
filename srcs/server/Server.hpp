/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:35:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/03 19:08:47 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
# include <iomanip>
# include <limits>
# include <cmath>
# include <cstdlib>
#include <cstdio>
#include <sstream>
#include <vector>
#include <map>
#include <fcntl.h>
#include <openssl/sha.h>
#include <poll.h>
#include <string>
#include <sys/socket.h>
#include "../client/Client.hpp"
#include "../channel/Channel.hpp"

class Client;
class Channel;

class Server
{
	private:
		int _port;

		std::string _hashedpassword;

		std::vector < Client* > _clients;
		std::vector < Channel* > _channels;
		std::string hashPassword(const std::string& password) const;

		//std::map < std::string, *Cmd > Commands; //to fix
	public:
		Server();
		~Server();
		void setPort(int port);
		void setPassword(const std::string& password);
		bool verifyPassword(const std::string& password) const;
		void run();
};

#endif
