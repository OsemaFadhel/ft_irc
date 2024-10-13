/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:33:07 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/13 18:34:18 by lnicoter         ###   ########.fr       */
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
			std::cout<<"Usr to delete "<<_usrData[i].first.getNickname()<<std::endl;
			std::string	partMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost "+ "PART " + this->getName() + " " + client.getNickname() + " is leaving the channel " + this->getName() + "\r\n";
			    // if (!reason.empty()) {
				// message += " :" + reason;
				// }

			_usrData.erase(_usrData.begin() + i);
			std::cout<<partMessage<<std::endl;
			send(client.getFd(), partMessage.c_str(), partMessage.length(), 0);
			break ;
		}
	}
}

void	Server::Part(std::string args, int clientSocket)
{
	std::vector<std::string>	numOfChannels = channelParser(args);
	Client		*client = getClient(clientSocket);

	for (size_t i = 0; i < _channels.size(); i++)
	{
		for (size_t j = 0; j < numOfChannels.size(); j++)
		{
			if (_channels[i].getName() == numOfChannels[j])
			{
				_channels[i].removeClient(*client);
				break ;
			}
		}
	}
}
