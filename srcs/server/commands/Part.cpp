/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:33:07 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/28 10:45:35 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"



/*
This method simply tells the other user of the channel who left it so
The referent client would change thanks for the messages
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

/*
This method make the user tell that is leaving the channel
+ calls the method to tell the other users on the channel too that is leaving
*/
void	Server::partLeavingMessage(Client usr, std::string channelName, std::string reason)
{
	std::string	partMessage = ":" + usr.getNickname() + " PART " + channelName;
	if (!reason.empty())
		partMessage += " "+reason;
	partMessage += "\r\n";
	send(usr.getFd(), partMessage.c_str(), partMessage.length(), 0);
	partLeavingMessageAll(channelName, usr.getNickname(), partMessage);
}

//this functions should return the index of the
//found user
int	Channel::findUsr(std::string usrNickname)
{
	for (size_t i = 0; i < _usrData.size(); i++)
	{
		if (_usrData[i].first.getNickname() == usrNickname)
			return i;
	}
	return -1;
}

/*
This method removes the usr from the vector _usrData
it checks if the usr is actually on the channel too
sending an error message in case it is not in
*/
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

/*
A reason Parser, made in case in the PART command is added a reason
for the leaving
*/
std::string	Server::takeReason(std::string &args)
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



/*

*/
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
		checkExistence(channelExist, channelIndex, _channels, numOfChannels, i);
		//non capisco come mai il messaggio viene mandato due volte causando l'errore guardo dopo
		if (channelExist && _channels[channelIndex].isInChannel(*client))
		{
			partLeavingMessage(*client, _channels[channelIndex].getName(), reason);
			_channels[channelIndex].removeClient(*client);
		}
	}
	//checking how many channels still have usrs
	deleteEmptyChannels();
}

/*
casi da gestire:
	eliminando lo stesso utente su più canali
	il messaggio di eliminazione viene inviato più volte ma sugli stessi canali
	N volte quanto i canali che deve abbandonare

*/
