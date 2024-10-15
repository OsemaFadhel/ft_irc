/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:33:07 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/15 16:06:35 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

//ci devo ripensare a come farla
//here i need to work with the clients vector<pair<client, int>> and the channel vector<pair<channel, int>>
/*
		void		partLeavingMessage(Client	usr, std::string channelName);
		void		partLeavingMessageAll(std::string channelName);

*/





void	Server::partLeavingMessageAll(std::string channelName, std::string usrName)
{
	std::string	partMessage = ":" + usrName + " PART :" + channelName + "\r\n";
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == channelName)
		{
			for (size_t j = 0; j < _channels[i].getUsrData().size(); j++)
			{
				if (_channels[i].getUsrData()[j].first.getNickname() != usrName)
				{
					std::cout<<"Allerting others that someone is leaving the channel"<<std::endl;
					std::cout<<"allerting "<<_channels[i].getUsrData()[j].first.getNickname()<<std::endl;
					send(_channels[i].getUsrData()[j].first.getFd(), partMessage.c_str(), partMessage.length(), 0);
				}
			}
		}
	}
}

void	Server::partLeavingMessage(Client	usr, std::string channelName)
{
	std::string	partMessage = ":" + usr.getNickname() + " PART :" + channelName + "\r\n";
	send(usr.getFd(), partMessage.c_str(), partMessage.length(), 0);
	partLeavingMessageAll(channelName, usr.getNickname());
}


void	Channel::removeClient(Client& client, std::string reason)
{
	(void)reason;
	std::string	partMessage = "";

	for (size_t i = 0; i < _usrData.size(); i++)
	{
		if (isInChannel(client))
		{
			std::cout<<"Usr to delete "<<_usrData[i].first.getNickname()<<std::endl;
			_usrData.erase(_usrData.begin() + i);
			i--;
		}
		else
		{
			//<channel> :You're not on that channel
			std::string notOnChannel = constructMessage(ERR_NOTONCHANNEL, this->getName().c_str());
			send(client.getFd(), notOnChannel.c_str(), notOnChannel.size(), 0);
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
	size_t						channelIndex;
	bool						channelExist = false;
	Client						*client = getClient(clientSocket);
	std::string					reason = takeReason(args);

	std::cout<<"numOfChannels "<<numOfChannels.size()<<std::endl;
	//main for
	for (size_t i = 0; i < _channels.size(); i++)
	{
		//loop for the check of the same channel
		checkExistence(channelExist, channelIndex, _channels, numOfChannels, i);

		if (channelExist)
		{
			_channels[channelIndex].removeClient(*client, reason);
			partLeavingMessage(*client, _channels[channelIndex].getName());
		}
	}

	//checking how many channels still have usrs
	deleteEmptyChannels();
}
