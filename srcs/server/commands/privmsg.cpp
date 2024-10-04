/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:05:20 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/04 14:30:29 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

//next thing to do []
//one is for messages in the channel
//one is for private messages between users

int	isChannel(std::string channelName)
{
	std::string prefixChecker = CHAR_FOR_CHANNEL_FIRST_LETTER;

	if ( prefixChecker.find_first_of(channelName[0]) != std::string::npos)
		return (1);
	return (0);
}

void	Server::Privmsg(std::string args, int clientsocket)
{
	(void)clientsocket;
	std::cout<<"PRIVMSG "<<args<<std::endl;
	if (isChannel(args))
	{
		;
	}
	else
	{
		//private message
		;
	}
}
