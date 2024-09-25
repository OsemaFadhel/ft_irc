/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:38:08 by lnicoter          #+#    #+#             */
/*   Updated: 2024/09/25 19:54:56 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"


/*
The implementation of the join function should be

if the user is already part of the channel the prefix changes
before goin and understanding the channel the first thing is to be sure
that the clients can enter it

The "args tha i receive is name of the channel"
And with the clientSocket i can retrieve the client that is going into
the channel

At the end i just made some checks to understand how many client the server socket could handle
it seems it depends only from the protocol that's it

- tomorrow we will start to do the join better though, i will be more focused on that
- In the rfc the amount of channels and keys you can ienter is not defined
- But you can insert keys only if you have one channel and you can't put more keys
- than the number of channels you put
*/
#include "../../../include/Server.hpp"

std::vector<std::string>	Server::channelParser(std::string args)
{
	//substr e find per spostare il puntatore alla prima virgola

	std::vector < std::string > numOfChannels;
	std::string onlyChannels = args.substr(0, args.find_first_of(" "));
	// std::vector < std::string > keys;
	size_t	i = 0;
	//loop for channels
	while (i != std::string::npos)
	{
		size_t pos = onlyChannels.find_first_of(",", i);
		if (pos != std::string::npos)
		{
			std::string temp = onlyChannels.substr(i, pos - i);
			// numOfChannels.push_back(onlyChannels.substr(i));
			std::cout << "temp: " << temp << std::endl;

			numOfChannels.push_back(temp);
			i = pos + 1;
		}
		else
		{
			std::string temp = onlyChannels.substr(i, pos - i);
			// numOfChannels.push_back(onlyChannels.substr(i, pos - i));
			std::cout << "temp: " << temp << std::endl;
			numOfChannels.push_back(temp);
			break;
		}
	}
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

//what to do now: having parsed the channels and the keys
//i must check if the channels it is like that i can check various stuff
//if the channel exist because if it doesn't exist i must create it and put it
//in the _channels vector
//if the channel exists i must check if the client is already in the channel
//

void	checkChannelExist(std::vector< std::string > numberOfChannels, std::vector < Channel > _channels, Client clientToInsert)
{
	for (size_t i = 0; i < numberOfChannels.size(); i++)
	{
		if (_channels.size() == 0)
			_channels.push_back(Channel(clientToInsert, numberOfChannels[i]));
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

					}

				}
			}
		}
	}
}

void	Server::Join(std::string args, int	clientSocket, std::vector< Channel > _channels)
{
	Client	clientToInsert = getClient(clientSocket);
	std::vector < std::string > numOfChannels;
	std::vector < std::string > keys;

	numOfChannels = channelParser(args);
	//the keys works only if the channel already exists
	keys = keyParser(args);


	(void)_channels;
}
