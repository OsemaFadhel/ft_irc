/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:45 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/04 14:07:05 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# define CHAR_FOR_CHANNEL_FIRST_LETTER "&#+!"
# define BAD_CHAR_FOR_CHANNEL " ,:"


#include "iostream"
#include "Server.hpp"
#include "Channel.hpp"

# define CHAR_FOR_CHANNEL_FIRST_LETTER "&#+!"
# define BAD_CHAR_FOR_CHANNEL " ,:"

class Client
{
	private:
		int			_fd;
		std::string _buffer;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		int _isRegistered; // 0 if not registered (only pass inserted), 1 if registered (nick and user inserted)
		//for all other commands, check if registered.
		//std::string _password;
		//std::string hashPassword(const std::string& password) const;
		//std::string _role; dont know if we need this here or in channel
	public:
		Client(int fd);
		~Client();
		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
		std::string getRealName() const;
		std::string getBuffer() const;
		int getIsRegistered() const;

		void setNickname(const std::string& nickname);
		void setUsername(const std::string& username);
		void setRealName(const std::string& realname);
		void setBuffer(const std::string& buffer);
		void setIsRegistered(int isRegistered);
		void clearBuffer();

		void appendBuffer(const char* buffer, int readsize);
};

	std::ostream&	operator<<(std::ostream& os, const Client& client);

#endif
