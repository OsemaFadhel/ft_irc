/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:45 by ofadhel           #+#    #+#             */
/*   Updated: 2024/07/29 16:34:56 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "iostream"
#include "./server/Server.hpp"

class client
{
	private:
		int _fd;
	public:
		Client(int fd) : _fd(fd){};
		~Client(){};
		int getFd() {return _fd};
};

#endif
