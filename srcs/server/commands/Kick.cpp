/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:14:00 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/19 18:16:15 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../../include/Server.hpp"



/*
Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
               [<comment>]

   The KICK command can be used to request the forced removal of a user
   from a channel.  It causes the <user> to PART from the <channel> by
   force.  For the message to be syntactically correct, there MUST be
   either one channel parameter and multiple user parameter, or as many
   channel parameters as there are user parameters.  If a "comment" is
   given, this will be sent instead of the default message, the nickname
   of the user issuing the KICK.

   The server MUST NOT send KICK messages with multiple channels or
   users to clients.  This is necessarily to maintain backward
   compatibility with old client software.
*/



/*
*missing checks:
	! the user that sends the kick command must be an operator
*/



void Server::Kick(std::string args, int clientSocket)
{
	std::vector<std::string>	numOfChannels = channelParser(args);
	//keyparser should parse the clients just fine
	std::vector<std::string>	numOfClient = keyParser(args);
	Client* superUser = getClient(clientSocket);

	for (size_t i = 0; i < numOfChannels.size(); i++)
	{
		//simple check if the channel exists
		if (!checkIfChannelExists(numOfChannels[i]))
		{
			std::string	errorMessage = constructMessage(ERR_NOSUCHCHANNEL, numOfChannels[i]);
			send(clientSocket, errorMessage.c_str(), errorMessage.size(), 0);
			return ;
		}
		else
		{
			//checking if the usr is an operator
			Channel *channel = getChannel(numOfChannels[i]);
			channel->printClients();
			if (!channel->isOperator(*superUser))
			{
				std::string	errorMessage = constructMessage(ERR_CHANOPRIVSNEEDED, superUser->getNickname(), numOfChannels[i]);
				send(clientSocket, errorMessage.c_str(), errorMessage.size(), 0);
				return ;
			}
			for (size_t j = 0; j < numOfClient.size(); j++)
			{
				Client clientToKick = channel->getClientByNickname(numOfClient[j]);
				//checks if the client exists
				if (clientToKick.getFd() == 0)
				{
					std::string	errorMessage = constructMessage(ERR_NOSUCHNICK, numOfClient[j]);
					send(clientSocket, errorMessage.c_str(), errorMessage.size(), 0);
					return ;
				}
				//kick the user from the channel
				if (channel->isInChannel(clientToKick))
				{
					Part(numOfChannels[i], clientToKick.getFd());
					std::string kickMessage = ":" + SERVERNAME + " KICK " + numOfChannels[i] + " " + clientToKick.getNickname() + " :Kicked by " + getClient(clientSocket)->getNickname() + "\r\n";
					send(clientSocket, kickMessage.c_str(), kickMessage.size(), 0);
					return ;
				}
				else
				{
					std::string	errorMessage = constructMessage(ERR_USERNOTINCHANNEL, clientToKick.getNickname(), numOfChannels[i]);
					send(clientSocket, errorMessage.c_str(), errorMessage.size(), 0);
				}
			}
		}
	}
}
