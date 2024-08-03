/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:11:54 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/03 19:08:53 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <map>
#include <string>
#include "../client/Client.hpp"
#include "../server/Server.hpp"

class Client;

class Channel
{
	private:
		std::map < std::string, Client* , std::string > _clients; //thinking name, client, operator or not
		std::string _name;
		std::string _topic;
		std::string _mode;
		std::string _password;
		int _limit;
	public:
		Channel();
		~Channel();
};

#endif
