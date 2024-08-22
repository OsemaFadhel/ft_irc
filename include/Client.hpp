/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:45 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/22 12:32:05 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "iostream"
#include "Server.hpp"
#include "Channel.hpp"

class Channel;

class Client
{
	private:
		int _fd;
		std::string _buffer;
		std::string _nickname;
		std::string _username;
		int _isRegistered; // 0 if not registered (only pass inserted), 1 if registered (nick and user inserted)
		//for all other commands, check if registered.
		//std::string _password;
		//std::string hashPassword(const std::string& password) const;
		//std::string _role; dont know if we need this here or in channel
		std::vector < Channel* > _channels;
	public:
		Client(int fd);
		~Client();
		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
		std::string getBuffer() const;
		int getIsRegistered() const;
		//std::string getPassword() const;

		void setNickname(const std::string& nickname);
		void setUsername(const std::string& username);
		void setBuffer(const std::string& buffer);
		void setIsRegistered(int isRegistered);
		void clearBuffer();

		void appendBuffer(const char* buffer, int readsize);
		//void setPassword(const std::string& password);
		//bool verifyPassword(const std::string& password) const;
};

#endif
