/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:38:08 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/01 17:21:07 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"


//substr e find per spostare il puntatore alla prima virgola
//new error: 2 channels that are going to be inserted with
//a space after the first , for example <channel1>, <channel2> the space messes up all the logic
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
	//why reach the end of this where a lot of channels are inserted
	return (numOfChannels);
}


std::vector< std::string >	Server::keyParser(std::string args)
{
	std::vector < std::string > keys;
	size_t	i = (args.find_first_of(" ")) + 1;
	//loop for keys
	while (i != std::string::npos)
	{
		size_t pos = args.find_first_of(",", i);
		if (pos != std::string::npos)
		{
			std::string temp = args.substr(i, pos - i);
			keys.push_back(temp);
			i = pos + 1;
		}
		else
		{
			std::string temp = args.substr(i, pos - i);
			keys.push_back(temp);
			break;
		}
	}
	for (size_t i = 0; i < keys.size(); i++)
		std::cout << "keys: " << keys[i] << std::endl;
	return (keys);
}

//Troubleshooting:
//




void	Server::checkChannelExist(std::vector< std::string > numberOfChannels, Client clientToInsert)
{
	std::cout<<"number of channels size: "<<numberOfChannels.size()<<std::endl;
	for (size_t i = 0; i < numberOfChannels.size(); i++)
	{
		if (_channels.size() == 0)
		{
			Channel newChannel = Channel(clientToInsert, numberOfChannels[i]);
			_channels.push_back(newChannel);
		}
		else
		{
			for (size_t j = 1; j < numberOfChannels.size(); j++)
			{
				if (_channels[i].getName() == numberOfChannels[j])
				{
					//if for checking if the user is in the channel
					if (_channels[i].isInChannel(clientToInsert))
					{
						std::string	errMessage = constructMessage(ERR_NICKNAMEINUSE, clientToInsert.getNickname());
						send(clientToInsert.getFd(), errMessage.c_str(), errMessage.size(), 0);
					}
					else
					{
						//!we are missing the checks for the keys like if the channel exists and stuff
						_channels[j].addClient(clientToInsert);
						std::cout<<GREEN<<"Client successfully added to the channel"<<RESET<<std::endl;
					}
				}
				else
				{
					std::cout<<"adding channel last case of ifs"<<std::endl;
					_channels.push_back(Channel(clientToInsert, numberOfChannels[i]));
				}
			}
		}
	}
}


void	Server::Join(std::string args, int	clientSocket)
{
	Client	*clientToInsert = getClient(clientSocket);
	std::vector < std::string > numOfChannels;
	// std::vector < std::string > keys;

	numOfChannels = channelParser(args);
	//the keys works only if the channel already exists
	// keys = keyParser(args);
	checkChannelExist(numOfChannels, *clientToInsert);
	channelCheck();
}
