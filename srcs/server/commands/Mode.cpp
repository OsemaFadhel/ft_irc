/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:15:48 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/28 10:46:15 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

/*
MODE - Change the channel’s mode:
· i: Set/remove Invite-only channel:
	+ -i: Set the channel to invite-only one argument only
	If this mode is set on a channel, a user must have received an INVITE
	for this channel before being allowed to join it.
	If they have not received an invite, they will receive an ERR_INVITEONLYCHAN (473)
	reply and the command will fail.
	MODE #channel +i
· t: Set/remove the restrictions of the TOPIC command to channel
operators
· k: Set/remove the channel key (password)
· o: Give/take channel operator privilege
· l: Set/remove the user limit to channel
*/

/*
i'll do a function that will parse the different types of modes
so i can handle how the modes are treated because some of them
do accept params after the :MODE #channel +/-flag
so depending on that i can develop a better error handling

->parsing the string: #channel +/-flag [hypothetical arguments]
->understanding what mode it is
->handling possible errors in case of more arguments than expected
->doing a function for any mode
->handle other type of errors accord
*/

/*
#channel +/-flag
#channel
flag flag[0] = +/-


*/
std::string	Server::modeParser(std::string args)
{
	size_t	i = args.find_first_not_of(" ");

	//i erase the spaces after the first trim i did for the str
	//so i will have the mode without spaces
	if (i == std::string::npos)
		args.erase(0, i);
	//+ or - and the mode
	std::string mode = args.substr(0, 2);

	return mode;
}

int	checkMode(std::string mode)
{
	if (MODES.find(mode[1]) == std::string::npos)
		return 0;
	return 1;
}

void	Server::setOrRemoveMode(std::string channelName, std::string mode, std::string hypotheticalArgs, int clientSocket)
{
	Channel	*channel = getChannel(channelName);
	std::cout<<"gotten mode "<<mode<<std::endl;
	if ((mode[0] != '+' || mode[0] != '-') && !checkMode(mode))
	{
		std::string	errMessage = constructMessage(ERR_UNKNOWNMODE, mode.c_str(), channelName.c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	switch (mode[1])
	{
		case 'i':
			channel->iMode(mode, hypotheticalArgs, clientSocket);
			break;
		case 't':
			channel->tMode(mode, hypotheticalArgs, clientSocket);
			break;
		case 'k':
			channel->kMode(mode, hypotheticalArgs, clientSocket);
			break;
		case 'o':
			channel->oMode(mode, hypotheticalArgs, clientSocket);
			break;
		case 'l':
			channel->lMode(mode, hypotheticalArgs, clientSocket);
			break;
	}
}


void	Server::Mode(std::string args, int clientSocket)
{
	std::string	channelName = channelParser(args)[0];
	std::string	hypotheticalArgs = "";

	if(!isChannel(channelName))
	{
		std::string	errMessage = constructMessage(ERR_NOSUCHCHANNEL, channelName);
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	Channel *channel = getChannel(channelName);
	if (!isInServer(channel))
	{
		std::string	errMessage = constructMessage(ERR_NOTONCHANNEL, channelName.c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	args = args.erase(0, channelName.size() + 1);
	std::string mode = modeParser(args);
	if (mode.empty())
	{
		std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "MODE");
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	// std::cout<<"what we have channel: "<<channelName<<std::endl;
	// std::cout<<"mode: "<<mode<<std::endl;
	args.erase(0, mode.size());
	size_t	i = args.find_first_not_of(" ");
	if (i != std::string::npos)
		args.erase(0, i);
	std::cout<<"args after mode parsing "<<args<<std::endl;
	if (!args.empty())
		hypotheticalArgs = args;
	std::cout<<"hypotheticalArgs "<<hypotheticalArgs<<std::endl;
	if (mode.empty())
	{
		std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "MODE");
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	setOrRemoveMode(channelName, mode, hypotheticalArgs, clientSocket);
}
