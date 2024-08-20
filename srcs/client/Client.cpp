/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:35:19 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/20 14:54:07 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Client.hpp"

Client::Client(int fd) : _fd(fd)
{
}

Client::~Client()
{
}

int Client::getFd() const
{
	return _fd;
}

std::string Client::getNickname() const
{
	return _nickname;
}

std::string Client::getUsername() const
{
	return _username;
}

std::string Client::getBuffer() const
{
	return _buffer;
}

void Client::setNickname(const std::string& nickname)
{
	_nickname = nickname;
}

void Client::setUsername(const std::string& username)
{
	_username = username;
}

void Client::setBuffer(const std::string& buffer)
{
	_buffer = buffer;
}

void Client::clearBuffer()
{
	_buffer.clear();
}

void Client::appendBuffer(const char* buffer, int readsize)
{
	if (_buffer.size() + readsize > 512)
	{
		std::cerr << "Error: Buffediscarding excess data.r overflow detected. Message to long" << std::endl;
		return;
	}
	_buffer += buffer;
}
