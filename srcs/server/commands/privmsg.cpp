/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:05:20 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/05 09:29:40 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

//next thing to do []
//one is for messages in the channel
//one is for private messages between users

int	isChannel(std::string channelName)
{
	std::string prefixChecker = CHAR_FOR_CHANNEL_FIRST_LETTER;

	if ( prefixChecker.find_first_of(channelName[0]) != std::string::npos)
		return (1);
	std::cout<<"death 💀"<<std::endl;
	return (0);
}

std::string extractMessage(const std::string& input)
{
	size_t	i = input.find(':');
	std::string	message = input.substr(i, input.size());
	return message;
}

std::string extractChannelName(const std::string& input)
{
	// Trova la posizione del primo carattere ':'
	size_t colonPos = input.find(':');

	// Se non troviamo il carattere ':', restituiamo l'intera stringa
	if (colonPos == std::string::npos)
	{
		return input; // Non c'è ':' quindi restituiamo l'intera stringa
	}

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
	std::cout<<"channelName "<<channelName<<std::endl;
	Client	*sender = getClient(clientSocket);
	std::string	message = ":"+sender->getNickname()+"!"+sender->getUsername()+"@host PRIVMSG "+channelName+" :"+usrMessage+"\r\n";


	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName().compare(channelName.c_str()))
		{
			// std::vector< std::pair< Client, int > >::iterator it;
			for (size_t j = 0; j < _channels[i].getUsrData().size(); j++)
			{
				if (_channels[i].getUsrData()[j].first.getNickname().compare(sender->getNickname()))
				{
					std::cout<<"sending message to the others"<<std::endl;
		 			send(_channels[i].getUsrData()[j].first.getFd(), message.c_str(), message.length(), 0);
				}
			}
			break;
		}
		else
		{
			std::cout<<"wrong one here we have "<<_channels[i].getName()<<std::endl;
		}
	}

}

void	Server::Privmsg(std::string args, int clientSocket)
{
	(void)clientSocket;
	std::string	realChannel = extractChannelName(args);
	std::string	message = extractMessage(args);
	std::cout<<"PRIVMSG "<<realChannel<<std::endl;
	if (isChannel(realChannel))
	{
		privmsgChannel(realChannel, clientSocket, message);
	}
	else
	{
		//private message
		;
	}
}
