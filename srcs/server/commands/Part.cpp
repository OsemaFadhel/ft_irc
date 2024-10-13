/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:33:07 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/13 20:47:45 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

//ci devo ripensare a come farla
//here i need to work with the clients vector<pair<client, int>> and the channel vector<pair<channel, int>>
void	Channel::removeClient(Client& client, std::string reason)
{
	(void)reason;
	std::string	partMessage = "";
	for (size_t i = 0; i < _usrData.size(); i++)
	{
		if (_usrData[i].first.getNickname() == client.getNickname())
		{
			std::cout<<"Usr to delete "<<_usrData[i].first.getNickname()<<std::endl;
			partMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost "+ "PART " + this->getName() + " " + client.getNickname() + " is leaving the channel " + this->getName();
			partMessage += "\r\n";
			std::cout<<"size before "<<_usrData.size()<<std::endl;
			_usrData.erase(_usrData.begin() + i);
			std::cout<<"size after "<<_usrData.size()<<std::endl;
			// std::cout<<"user found "<<_usrData.begin() + i<<std::endl;
			std::cout<<partMessage<<std::endl;
			send(client.getFd(), partMessage.c_str(), partMessage.length(), 0);
			std::cout<<_usrData[i].first<<std::endl;
		}
		if (!partMessage.empty())
		{
			std::cout<<"who's getting this message damnnnnn "<<_usrData[i].first.getNickname()<<std::endl;
			send(_usrData[i].first.getFd(), partMessage.c_str(), partMessage.length(), 0);
		}
	}
}

//PART #channel, cmldffk :reason
std::string	Server::takeReason(std::string args)
{
	size_t i = args.find_first_of(':', 0);
	std::string	reason;

	if (i != std::string::npos)
	{
		reason = args.substr(i, args.size());
		std::cout<<"reason "<< reason <<std::endl;
		return reason;
	}
	return "";
}

void	Server::Part(std::string args, int clientSocket)
{
	std::vector<std::string>	numOfChannels = channelParser(args);
	Client		*client = getClient(clientSocket);
	std::string	reason = takeReason(args);
	for (size_t i = 0; i < _channels.size(); i++)
	{
		for (size_t j = 0; j < numOfChannels.size(); j++)
		{
			if (_channels[i].getName() == numOfChannels[j])
			{
				_channels[i].removeClient(*client, reason);
				break ;
			}
		}
	}
}
