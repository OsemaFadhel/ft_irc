/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:45 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/28 10:32:38 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP


#include "iostream"
#include "Server.hpp"
#include "Channel.hpp"

# define CHAR_FOR_CHANNEL_FIRST_LETTER "&#+!"
# define BAD_CHAR_FOR_CHANNEL " ,:"

class Client
{
	private:
		int _fd;
		std::string _buffer;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
		int _isRegistered; // 0 if not registered (only pass inserted), 1 if registered (nick and user inserted)

	public:
		Client(int fd);
		~Client();
		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
		std::string getRealName() const;
		std::string getBuffer() const;
		std::string getHostname() const;
		int getIsRegistered() const;

		void setNickname(const std::string& nickname);
		void setUsername(const std::string& username);
		void setRealName(const std::string& realname);
		void setHostname(const std::string& hostname);
		void setBuffer(const std::string& buffer);
		void setIsRegistered(int isRegistered);
		void clearBuffer();

		void appendBuffer(const char* buffer, int readsize);
};

	std::ostream&	operator<<(std::ostream& os, const Client& client);

#endif
