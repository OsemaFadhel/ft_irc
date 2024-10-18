/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:14:00 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/18 19:52:15 by lnicoter         ###   ########.fr       */
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
void Server::Kick(std::string args, int clientSocket)
{
	std::vector<std::string>	numOfChannels = channelParser(args);
	//keyparser should parse just fine
	std::vector<std::string>	numOfClient = keyParser(args);

	if (numOfChannels.size() < numOfClient.size())
	{
		std::string	erroMessage = constructMessage(ERR_NEEDMOREPARAMS, "KICK");
	}
}
