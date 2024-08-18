/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:45 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/18 21:05:09 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "iostream"
#include "../server/Server.hpp"
#include "../channel/Channel.hpp"

class Channel;

class Client
{
	private:
		int _fd;
		std::string _buffer;
		std::string _nickname;
		std::string _username;

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
		//std::string getPassword() const;

		void setNickname(const std::string& nickname);
		void setUsername(const std::string& username);
		void setBuffer(const std::string& buffer);

		void appendBuffer(const char *buffer);
		//void setPassword(const std::string& password);
		//bool verifyPassword(const std::string& password) const;
};

#endif
