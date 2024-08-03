/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:45 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/03 19:07:12 by ofadhel          ###   ########.fr       */
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
		std::string _nickname;
		std::string _username;
		//std::string _role; dont know if we need this here or in channel
		std::vector < Channel* > _channels;
	public:
		Client(int fd);
		~Client(){};
		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
		void setNickname(const std::string& nickname);
		void setUsername(const std::string& username);
};

#endif
