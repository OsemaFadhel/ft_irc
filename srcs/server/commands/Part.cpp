/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:33:07 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/21 15:17:37 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

//ci devo ripensare a come farla
//here i need to work with the clients vector<pair<client, int>> and the channel vector<pair<channel, int>>
/*
		void		partLeavingMessage(Client	usr, std::string channelName);
		void		partLeavingMessageAll(std::string channelName);

*/





void	Server::partLeavingMessageAll(std::string channelName, std::string usrName, std::string partMessage)
{
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

void	Server::partLeavingMessage(Client usr, std::string channelName, std::string reason)
{
	std::string	partMessage = ":" + usr.getNickname() + " PART " + channelName;
	if (!reason.empty())
		partMessage += " "+reason;
	partMessage += "\r\n";
	std::cout<<"message I'm going to send "<<partMessage<<std::endl;
	send(usr.getFd(), partMessage.c_str(), partMessage.length(), 0);
	partLeavingMessageAll(channelName, usr.getNickname(), partMessage);
}

//this functions should return the index of the
//k
int	Channel::findUsr(std::string usrNickname)
{
	for (size_t i = 0; i < _usrData.size(); i++)
	{
		if (_usrData[i].first.getNickname() == usrNickname)
			return i;
	}
	return -1;
}

//_usrs.erase(std::remove(_usrs.begin(), _usrs.end(), usr), _usrs.end());
//if there more clients it deletes more than one why thought
void	Channel::removeClient(Client& client)
{
	std::string	partMessage = "";

	std::cout<<RED<<"Target Client nickname -> "<<client.getNickname()<<RESET<<std::endl;
	for (size_t i = 0; i < _usrData.size(); i++)
	{
		//i must change the condition
		int	index = findUsr(client.getNickname());
		if (index != -1)
		{
			_usrData.erase(_usrData.begin() + index);
			break;
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
//the substring
std::string	Server::takeReason(std::string args)
{
	try
	{
		size_t i = (args.find_last_of(':'));
		if (i != std::string::npos)
		{
			std::string	reason = args.substr(i, args.size());
			std::cout<<"reason gained is wrong for sure "<<reason<<std::endl;
			//il parsing di reason è sbagliato
			return reason;
		}
	}
	catch(std::out_of_range &e)
	{
		std::cout<<e.what()<<std::endl;
	}
	return "";
}



//args = #channel1,&channel2,&channel3(find_firs_of)     (last_not_of ' ') <reason>
//pos
void	Server::Part(std::string args, int clientSocket)
{
	std::vector<std::string>	numOfChannels = channelParser(args);
	bool						channelExist = false;
	Client						*client = getClient(clientSocket);
	std::string					reason = takeReason(args);
	size_t						channelIndex;

	// std::cout<<"numOfChannels "<<numOfChannels.size()<<std::endl;
	//main for
	for (size_t i = 0; i < _channels.size(); i++)
	{
		//loop for the check of the same channel
		checkExistence(channelExist, channelIndex, _channels, numOfChannels, i);

		if (channelExist)
		{
			_channels[channelIndex].removeClient(*client);
			partLeavingMessage(*client, _channels[channelIndex].getName(), reason);
		}
	}

	//checking how many channels still have usrs
	deleteEmptyChannels();
}

/*
la situazione è la seguente:
	essendo che con partAll devo eliminare più volte lo stesso utente
	questo significa
*/

// void	turnOutFirst(std::vector<std::pair <Client, int> > )
// {

// }

// void	Channel::removeUsrEasierBeta(const Client& usr)
// {
// 	_usrData.erase(std::remove_if(_usrData.begin(), _usrData.end(),
// 	[&usr](const std::pair<Client, int>& p)
// 	{
// 		return p.first;
// 	}),
// 	_usrData.end());
// }





