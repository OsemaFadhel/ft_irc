/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:04:35 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/28 10:47:26 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

//one channel and one nickname be aware
//<nickname> <channel>
//how it should be sent
//:<inviter> INVITE <target> <channel>

void	Server::Invite(std::string args, int clientSocket)
{
	std::vector<std::string> channelName = keyParser(args);
	std::vector<std::string> target = channelParser(args);
	Client*	inviter = getClient(clientSocket);

	if (channelName.size() != 1 || target.size() != 1)
	{
		std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "INVITE");
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}

	Client* invitedClient = getClientByNickname(target[0]);

	if (!invitedClient)
	{
		std::string	errMessage = constructMessage(ERR_NOSUCHNICK, target[0].c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}

	if (!checkIfChannelExists(channelName[0]))
	{
		std::string	errMessage = constructMessage(ERR_NOSUCHCHANNEL);
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}

	Channel*	channelWhereInvited = getChannel(channelName[0]);

	if (!channelWhereInvited->isInChannel(*inviter))
	{
		std::string	errMessage = constructMessage(ERR_NOTONCHANNEL, inviter->getNickname().c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	else if (channelWhereInvited->isInChannel(*invitedClient))
	{
		std::string	errMessage = constructMessage(ERR_USERONCHANNEL, invitedClient->getNickname().c_str(), channelWhereInvited->getName().c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	channelWhereInvited->setWhoInvited(clientSocket);
	std::string success = constructMessage(RPL_INVITING, inviter->getNickname().c_str(), invitedClient->getNickname().c_str(), channelWhereInvited->getName().c_str());
	std::cout<<"first success check "<<success<<std::endl;
	send(clientSocket, success.c_str(), success.size(), 0);
	success = ":" + inviter->getNickname() + " INVITE " + invitedClient->getNickname() + " " + channelWhereInvited->getName() + "\r\n";
	std::cout<<"second success check "<<success<<std::endl;
	send(invitedClient->getFd(), success.c_str(), success.size(), 0);
}

