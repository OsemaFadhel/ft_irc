/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:35:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/18 21:11:24 by ofadhel          ###   ########.fr       */
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
#include "Replies.hpp"
#include <arpa/inet.h>

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
		std::vector < int > _newfds;
		std::string hashPassword(const std::string& password) const;
		struct sockaddr_in6 _serverAddr;

		//std::map < std::string, *Cmd > Commands; //to fix
	public:
		Server();
		~Server();
		void setPort(int port);
		int getPort() const;
		void setPassword(const std::string& password);
		bool verifyPassword(const std::string& password) const;
		void run();
		void createSocket();
		void setMaxfds(int &maxfds, fd_set &readfds);
		int acceptClient(int *selectfd);
		void ClientDisconnect(int clientSocket, size_t &i);
		void handleMessage(char* buffer, int readSize, int clientSocket);
		int handleCarriageReturn(char* buffer, int fd);
		void processCommand(std::string buffer, int clientSocket);

};

// Macros for ANSI escape codes
#define RESET      "\033[0m"   // Reset all attributes
#define BOLD       "\033[1m"   // Bold text
#define UNDERLINE  "\033[4m"   // Underlined text

// Foreground colors
#define BLACK      "\033[30m"
#define RED        "\033[31m"
#define GREEN      "\033[32m"
#define YELLOW     "\033[33m"
#define BLUE       "\033[34m"
#define MAGENTA    "\033[35m"
#define CYAN       "\033[36m"
#define WHITE      "\033[37m"

// Background colors
#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

#endif
