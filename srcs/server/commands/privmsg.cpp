/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:05:20 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/12 14:03:22 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

//next thing to do []
//one is for messages in the channel
//one is for private messages between users

int	isChannel(std::string channelName)
{
	std::string prefixChecker = CHAR_FOR_CHANNEL_FIRST_LETTER;

	if (prefixChecker.find_first_of(channelName[0]) != std::string::npos)
		return (1);
	return (0);
}

//can't be used for a private msg
std::string extractMessage(const std::string& input)
{
	size_t	i = input.find(':');
	std::cout<<"eccoci "<<i<<std::endl;
	if (i == std::string::npos)
		return "";
	std::string	message = input.substr(i, input.size());
	return message;
}

std::vector<std::string> extractUsrMsgToSend(const std::string& input)
{
	std::string	usr = (input.find_first_of(':') == std::string::npos) ? "" : input.substr(0, input.find_first_of(':'));
	std::string	message = (input.find_first_of(':') == std::string::npos) ? "" : input.substr(input.find_first_of(':'), input.size());

	if (usr == "" || message == "")
	{
		//then you'll check if vector is empty later
		std::vector<std::string>	usrAndMessage;
		usrAndMessage.push_back(usr);
		usrAndMessage.push_back(message);
		std::cout<<"death"<<std::endl;
		return usrAndMessage;
	}
	// usr.erase()
	//chekc if message || usr are npos in case send an error to the client in question!!!
	// std::cout<<"Input received sending to user case "<<input<<std::endl;
	// std::cout<<"user that needs to receive the message"<<GREEN<<usr<<RESET<<"that's it"<<std::endl;
	// std::cout<<"message in question"<<GREEN<<message<<RESET<<"that's it"<<std::endl;
	usr = usr.erase(usr.find_last_of(' '));
	std::vector<std::string>	usrAndMessage;
	usrAndMessage.push_back(usr);
	usrAndMessage.push_back(message);
	return usrAndMessage;
}

std::string extractChannelName(const std::string& input)
{
	// Trova la posizione del primo carattere ':'
	size_t colonPos = input.find(':');

	// Se non troviamo il carattere ':', restituiamo l'intera stringa
	if (colonPos == std::string::npos)
		return input; // Non c'è ':' quindi restituiamo l'intera stringa

	// Restituiamo la sottostringa che va dall'inizio fino al carattere ':'
	return input.substr(0, colonPos);
}

//better implementation
	// Channel	*myChannel = getChannel(channelName);
	// if (myChannel)
	// {
	// std::vector< std::pair< Client, int > >::iterator it;
	// for (it = myChannel->getUsrData().begin(); it != myChannel->getUsrData().end(); it++)
	// {
		// if (it->first.getFd() != clientSocket)
		// {
		// 	std::cout<<"sending message to the others"<<std::endl;
		// 	send(it->first.getFd(), message.c_str(), message.length(), 0);
		// }
	// }
	// }
// 	else
// 		std::cout<<"Channel not found"<<std::endl;

void	Server::privmsgChannel(std::string channelName, int clientSocket, std::string usrMessage)
{
	channelName = channelName.erase(channelName.find_first_of(' '));
	std::cout<<"channelName "<<channelName<<std::endl;
	Client	*sender = getClient(clientSocket);
	std::string	message = ":"+sender->getNickname()+"!"+sender->getUsername()+"@host PRIVMSG "+channelName+" :"+usrMessage+"\r\n";

	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (!_channels[i].getName().compare(channelName.c_str()))
		{
			if (_channels[i].isInChannel(*sender))
			{
				for (size_t j = 0; j < _channels[i].getUsrData().size(); j++)
				{
					if (_channels[i].getUsrData()[j].first.getNickname().compare(sender->getNickname()))
					{
						std::cout<<"sending message to the others"<<std::endl;
						send(_channels[i].getUsrData()[j].first.getFd(), message.c_str(), message.length(), 0);
					}
				}
			}
			else
			{
				std::string errMessage = constructMessage(ERR_NOTONCHANNEL, sender->getNickname().c_str(), channelName);
				send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
			}
			break;
		}
		else
		{
			std::cout<<"wrong one here we have "<<channelName<<std::endl;
			break;
		}
	}

}




//BAN checks are not requested by the subject
void	Server::sendPrivateMsg(int clientSocket, std::vector<std::string> usrAndMsg)
{
	Client	receivingUser(0);

	std::cout<<"usrAndMsg[0] "<<usrAndMsg[0]<<std::endl;
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i]->getNickname().compare(usrAndMsg[0]) == 0 && _clients[i]->getFd() != clientSocket)
		{
			receivingUser = *_clients[i];
			break;
		}
	}
	if (receivingUser.getFd() == 0)
	{
		std::string	errMessage = constructMessage(ERR_NOSUCHNICK, usrAndMsg[0]);
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	std::string	message = ":"+getClient(clientSocket)->getNickname()+"!"+getClient(clientSocket)->getUsername()+"@host PRIVMSG "+receivingUser.getNickname()+" "+usrAndMsg[1]+"\r\n";
	send(receivingUser.getFd(), message.c_str(), message.length(), 0);
}

void	Server::Privmsg(std::string args, int clientSocket)
{
	std::string	realChannel = extractChannelName(args);
	std::cout<<"args received "<<args<<std::endl;

	if (isChannel(realChannel))
	{
		std::string	message = extractMessage(args);
		if (message.empty())
		{
			std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "PRIVMSG");
			send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
			return ;
		}
		privmsgChannel(realChannel, clientSocket, message);
	}
	else
	{
		std::vector<std::string>	usrAndMsg = extractUsrMsgToSend(args);
		if (usrAndMsg[0].empty() || usrAndMsg[1].empty())
		{
			if (usrAndMsg[0].empty())
			{
				std::string	errMessage = constructMessage(ERR_NORECIPIENT, "PRIVMSG");
				send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
				return ;
			}
			else
			{
				std::string	errMessage = constructMessage(ERR_NOTEXTTOSEND, "PRIVMSG");
				send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
				return ;
			}
		}
		//private message
		//this in kvirc is not sent by the channel ui
		//but is instead is sent manually from the
		sendPrivateMsg(clientSocket, usrAndMsg);
	}
}

/*
	errors to handle

	404    ERR_CANNOTSENDTOCHAN (this should be implemented after you have implemented the operators)
              "<channel name> :Cannot send to channel"

         - Sent to a user who is either (a) not on a channel
           which is mode +n or (b) not a chanop (or mode +v) on
           a channel which has mode +m set or where the user is
           banned and is trying to send a PRIVMSG message to
           that channel.
		   This is generally sent in response to channel modes, such as a channel being moderated and the client
		   not having
		   permission to speak on the channel, or not being joined to a channel with the no external
		   messages mode set.

	 442    ERR_NOTONCHANNEL (very generic error i don't know how to implement it)
	 		<client> <channel> :You're not on that channel"

         - Returned by the server whenever a client tries to
           perform a channel affecting command for which the
           client isn't a member.



*/
