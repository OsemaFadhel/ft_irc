/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:30:20 by ofadhel           #+#    #+#             */
/*   Updated: 2024/11/12 11:53:31 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

int checkErrors1(std::string chan, int fd)
{
	if (chan.empty()) //no channel name
	{
		std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "TOPIC");
		return send(fd, errMessage.c_str(), errMessage.size(), 0), 1;
	}
	if (chan[0] == '!') //channel no mode is set
	{
		std::string	errMessage = constructMessage(ERR_NOCHANMODES, chan.c_str());
		return send(fd, errMessage.c_str(), errMessage.size(), 0), 1;
	}
	return 0;
}

int checkErrors2(std::string chan, int fd, Channel *channel, Client *client)
{
	if (channel == 0) //channel does not exist
	{
		std::string	errMessage = constructMessage(ERR_NOSUCHCHANNEL, chan.c_str());
		return send(fd, errMessage.c_str(), errMessage.size(), 0), 1;
	}
	//user is not in the channel
	if (channel->isInChannel(*client) == 0)
	{
		std::string	errMessage = constructMessage(ERR_USERNOTINCHANNEL, client->getNickname().c_str(), chan.c_str());
		return send(fd, errMessage.c_str(), errMessage.size(), 0), 1;
	}

	return 0;
}

void Server::sendToChannel(Channel *channel, Client *sender, std::string chan, std::string message)
{
	std::string messageToSend = ":"+sender->getNickname()+"!"+sender->getUsername()+"@host TOPIC "+ chan + " " + message + "\r\n";
	std::vector<std::pair<Client, int> >	usrData = channel->getUsrData();

	for (size_t i = 0; i < usrData.size(); i++)
	{
		if (usrData[i].first.getFd() != sender->getFd())
			send(usrData[i].first.getFd(), messageToSend.c_str(), messageToSend.size(), 0);
	}
}

void Server::Topic(std::string args, Client *client)
{
	int	fd = client->getFd();
	std::string	chan = extractChannelName(args);
	chan.erase(chan.find_last_not_of(" \t") + 1);

	if (checkErrors1(chan, fd))
		return;

	if (isChannel(chan))
	{
		Channel	*channel = getChannel(chan);

		if (checkErrors2(chan, fd, channel, client))
			return;

		//mode +t is set to false only the operator can change the topic
		if (channel->getMode().find('t')->second == true)
		{
			//check if the user is an operator
			if (channel->isOperator(*client) == 0) //user is not an operator
			{
				std::string	errMessage = constructMessage(ERR_CHANOPRIVSNEEDED, chan.c_str());
				return send(fd, errMessage.c_str(), errMessage.size(), 0), void();
			}
		}

		std::string	message = extractMessage(args);
		message.erase(0, message.find_first_not_of(" \t"));
		message.erase(message.find_last_not_of(" \t") + 1);

		if (message.empty())
		{
			if (channel->getTopic() == "")
			{
				std::string	errMessage = constructMessage(RPL_NOTOPIC, chan.c_str());
				send(fd, errMessage.c_str(), errMessage.size(), 0);
			}
			else
			{
				std::string	errMessage = constructMessage(RPL_TOPIC, chan.c_str(), channel->getTopic().c_str());
				send(fd, errMessage.c_str(), errMessage.size(), 0);
			}
		}
		//check if message is only
		else if (message.size() > 1 && message[0] == ':')
		{
			//remove prefix :
			sendToChannel(channel, client, chan, message);
			message.erase(0, 1);
			channel->setTopic(message);
			std::string	errMessage = constructMessage(RPL_TOPIC, chan.c_str(), message.c_str());
			send(fd, errMessage.c_str(), errMessage.size(), 0);
		}
		else
		{
			channel->setTopic(message);
			std::string	errMessage = constructMessage(RPL_TOPIC, chan.c_str(), message.c_str());
			send(fd, errMessage.c_str(), errMessage.size(), 0);
		}
	}
	else
	{
		std::string	errMessage = constructMessage(ERR_NOSUCHCHANNEL, chan.c_str());
		send(fd, errMessage.c_str(), errMessage.size(), 0);
	}
}
