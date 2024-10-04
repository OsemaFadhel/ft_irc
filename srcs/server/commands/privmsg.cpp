/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:05:20 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/04 12:25:09 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

//next thing to do []
//one is for messages in the channel
//one is for private messages between users

int	isChannel(std::string channelName)
{
	if (channelName[0] == '#')
		return (1);
	return (0);
}

void	Server::Privmsg(std::string args, int clientsocket)
{

}
