/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:35:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/04 12:52:04 by ofadhel          ###   ########.fr       */
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
#include "Client.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include <arpa/inet.h>
#include <csignal>

# define SERVERNAME std::string("FT_IRC")
# define VERSION std::string("1.0.0")
# define DATE std::string("2024/08/01")


class Client;
class Channel;

typedef struct socketdata
{
	int id;
	std::string buffer;
} socketdata;

class Server
{
	private:
		int _port;
		int _serverSocket; //tcp
		std::string _password;
		std::vector < Client* > _clients;
		std::vector < Channel > _channels;
		std::vector < socketdata > _newfds;
		struct sockaddr_in _serverAddr;

	public:
		Server();
		~Server();
		void setPort(int port);
		int getPort() const;
		void setPassword(const std::string& password);
		bool verifyPassword(const std::string& password) const;
		Client* getClient(int clientSocket);
		int getClientIndex(int clientSocket);;
		void removeClient(int clientSocket);
		void killServer();

		void run();
		void createSocket();
		void setMaxfds(int &maxfds, fd_set &readfds);
		void startLoop(fd_set &readfds, int &maxfds);
		int acceptClient(int *selectfd);
		void clientDisconnect(int clientSocket, size_t &i);
		void checkClientActivity(fd_set& readfds);

		void handleMessage(std::string buffer, int readSize, int clientSocket, size_t &i);
		void trimCommand(std::string &command);
		std::vector<std::string> splitCommand(std::string command);
		int findCarriageReturn(char* buffer, int readSize);
		int handleCarriageReturn(char* buffer, int fd, int readSize, size_t &i);
		void processCommand(std::string buffer, int clientSocket, size_t &i);

		/*commands maybe create static class*/
		void Cap(int clientSocket);
		void Ping(Client *client, int clientSocket, std::string &message);
		void Quit(std::string args, int clientSocket, size_t &i);
		void Pass(std::string args, int clientSocket);
		void Nick(std::string args, int clientSocket);
		void User(std::string args, int clientSocket);

		/*Join command and functions by lnicoter*/
		/* Join behaviour
			Syntax:
				JOIN <channel>,....
				JOIN <channel>,....  <key>,....
				between channel and key there is a space that's how we can differentiate them
		*/
		void								Join(std::string args, int	clientSocket);
		std::vector< std::string >			channelParser(std::string args);
		std::vector< std::string >			keyParser(std::string args);
		void	checkChannelExist(std::vector< std::string > numberOfChannels, Client clientToInsert);
		//checking functions of server by lnicoter
		void	valuesCheck(Client clientToInsert);
		void	channelCheck();
		void	joinCreateChanMsg(Client clientToInsert, std::string channelName);
		void	listOfUsersMsg(std::string channelName);

		/*Privmsg command and functions by lnicoter*/
		void	Privmsg(std::string args, int clientSocket);

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
