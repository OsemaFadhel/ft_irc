/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:33:07 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/12 19:48:35 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

//ci devo ripensare a come farla
//here i need to work with the clients vector<pair<client, int>> and the channel vector<pair<channel, int>>
void	Channel::removeClient(Client& client)
{
	for (size_t i = 0; i < _usrData.size(); i++)
	{
		if (_usrData[i].first.getNickname() == client.getNickname())
		{
			_usrData.erase(_usrData.begin() + i);
			break ;
		}
	}
}

void	Server::Part(std::string args, int clientSocket)
{
	std::string	channelName = args.substr(0, args.find_first_of(' '));
	Client		*client = getClient(clientSocket);

	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == channelName)
		{
			_channels[i].removeClient(*client);
			break ;
		}
	}
}
