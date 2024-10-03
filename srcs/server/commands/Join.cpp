/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:38:08 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/03 15:01:23 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"


//substr e find per spostare il puntatore alla prima virgola
//new error: 2 channels that are going to be inserted with
//a space after the first , for example <channel1>, <channel2> the space messes up all the logic [SOLVED]
std::vector<std::string>	Server::channelParser(std::string args)
{

	std::vector < std::string > numOfChannels;
	std::string onlyChannels = args.substr(0, args.find_first_of(" "));
	// std::vector < std::string > keys;

	size_t	i = 0;
	//loop for channels
	while (i != std::string::npos)
	{
		size_t pos = onlyChannels.find_first_of(",", i);
		std::string temp;
		if (pos != std::string::npos)
		{
			temp = onlyChannels.substr(i, pos - i);
			// numOfChannels.push_back(onlyChannels.substr(i));
			std::cout << "temp1: " << temp << std::endl;
			i = pos + 1;
		}
		else
		{
			temp = onlyChannels.substr(i);
			// numOfChannels.push_back(onlyChannels.substr(i, pos - i));
			std::cout << "temp2: " << temp << std::endl;
			// break;
			i = std::string::npos;
		}
		temp.erase(0, temp.find_first_not_of(" "));
		temp.erase(temp.find_last_not_of(" ") + 1);

		// Controlla se la stringa è valida (non vuota e non contiene spazi)
		if (!temp.empty() && temp.find(' ') == std::string::npos)
		{
			numOfChannels.push_back(temp);
			std::cout << "Channel added: " << temp << std::endl;
		}
		else
		{
			std::cout << "Invalid channel ignored: " << temp << std::endl;
		}
	}
	return (numOfChannels);
}


std::vector< std::string >	Server::keyParser(std::string args)
{
	std::vector < std::string > keys;
	size_t	i = (args.find_first_of(" ")) + 1;
	std::string temp;

	//loop for keys
	while (i != std::string::npos)
	{
		size_t pos = args.find_first_of(",", i);
		if (pos != std::string::npos)
		{
			temp = args.substr(i, pos - i);
			keys.push_back(temp);
			i = pos + 1;
		}
		else
		{
			temp = args.substr(i, pos - i);
			keys.push_back(temp);
			break;
		}

		temp.erase(0, temp.find_first_not_of(" "));
		temp.erase(temp.find_last_not_of(" ") + 1);

		// Controlla se la stringa è valida (non vuota e non contiene spazi)
		if (!temp.empty() && temp.find(' ') == std::string::npos)
		{
			keys.push_back(temp);
			std::cout << "Key added: " << temp << std::endl;
		}
		else
		{
			std::cout << "Invalid Key ignored: " << temp << std::endl;
		}
	}

	for (size_t i = 0; i < keys.size(); i++)
		std::cout << "keys: " << keys[i] << std::endl;
	return (keys);
}

//there's something else
//channel created but the messages are not well translated

void	Server::listOfUsersMsg(std::string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == channelName)
		{
			std::string serverMessage = ":" + SERVERNAME + " 353 " + SERVERNAME + " = " + channelName + " :";
			for (size_t j = 0; j < _channels[i].getUsrData().size(); j++)
			{
				serverMessage += _channels[i].getUsrData()[j].first.getNickname() + " ";
			}
			serverMessage += "\r\n";
			send(_channels[i].getUsrData()[0].first.getFd(), serverMessage.c_str(), serverMessage.size(), 0);
		}
	}
	std::string channelMessage = ":" + SERVERNAME + " 366 " + channelName + " :End of NAMES list\r\n";
	send(_channels[0].getUsrData()[0].first.getFd(), channelMessage.c_str(), channelMessage.size(), 0);
}

void	Server::joinCreateChanMsg(Client clientToInsert, std::string channelName)
{
	std::cout<<GREEN<<"joinCreateChanMsg"<<RESET<<std::endl;
	std::cout<<"channel to create/join: "<<channelName<<std::endl;
	std::string serverMessage = ":" + clientToInsert.getNickname() + " JOIN :" + channelName + "\r\n";
	send(clientToInsert.getFd(), serverMessage.c_str(), serverMessage.size(), 0);
	listOfUsersMsg(channelName);
}

void	Server::checkChannelExist(std::vector< std::string > numberOfChannels, Client clientToInsert)
{
	for (size_t i = 0; i < numberOfChannels.size(); i++)
	{
		if (_channels.size() == 0)
		{
			Channel newChannel = Channel(clientToInsert, numberOfChannels[i]);
			_channels.push_back(newChannel);
			//i send the message to make the client create/join the channel
			joinCreateChanMsg(clientToInsert, newChannel.getName());
		}
		else
		{
			for (size_t j = 0; j < _channels.size(); j++)
			{
				if (_channels[j].getName() == numberOfChannels[i])
				{
					//if for checking if the user is in the channel
					if (_channels[j].isInChannel(clientToInsert))
					{
						std::string	errMessage = constructMessage(ERR_NICKNAMEINUSE, clientToInsert.getNickname());
						send(clientToInsert.getFd(), errMessage.c_str(), errMessage.size(), 0);
					}
					else
					{
						//!we are missing the checks for the keys like if the channel exists and stuff
						_channels[j].addClient(clientToInsert);
						std::cout<<GREEN<<"Client successfully added to the channel"<<RESET<<std::endl;
						joinCreateChanMsg(clientToInsert, _channels[j].getName());
					}
				}
				else
				{
					_channels.push_back(Channel(clientToInsert, numberOfChannels[i]));
					joinCreateChanMsg(clientToInsert, _channels[_channels.size() - 1].getName());
				}
			}
		}
	}
}


/*
** Troubleshooting
** The parsing of the keys is on point and it works very well
** I should do the same checks for the keyparser
** Following another irc it seems the keys are ignored if the channel doesn't exist and it's
** the first time

** I must create a channel section in the irc client reference
** the answers are hidden in the RFC


   If a JOIN is successful, the user receives a JOIN message as
   confirmation and is then sent the channel's topic (using RPL_TOPIC) and
   the list of users who are on the channel (using RPL_NAMREPLY), which
   MUST include the user joining.

! the modes defines if there's a password or not

 Channels with '+' as prefix do not support channel modes.  This means
   that all the modes are unset, with the exception of the 't' channel
   flag which is set.
A user who creates a channel with the character '!' as prefix is
   identified as the "channel creator".  Upon creation of the channel,
   this user is also given channel operator status.
*/

void	Server::Join(std::string args, int	clientSocket)
{
	Client	*clientToInsert = getClient(clientSocket);
	std::vector < std::string > numOfChannels;
	std::vector < std::string > keys;

	numOfChannels = channelParser(args);
	//the keys works only if the channel already exists
	// keys = keyParser(args);
	for (size_t k = 0; k < keys.size(); k++)
		std::cout << "keys: " << keys[k] << std::endl;

	checkChannelExist(numOfChannels, *clientToInsert);
	// channelCheck();
}

