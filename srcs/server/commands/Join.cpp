/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:38:08 by lnicoter          #+#    #+#             */
/*   Updated: 2024/09/30 17:39:53 by lnicoter         ###   ########.fr       */
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

//Troubleshooting:
//


void	Server::valuesCheck(Client clientToInsert)
{
	std::cout<<"Client nickname: "<<clientToInsert.getNickname()<<std::endl;
	std::cout<<"Client fd: "<<clientToInsert.getFd()<<std::endl;
}


void	Server::checkChannelExist(std::vector< std::string > numberOfChannels, Client clientToInsert)
{
	for (size_t i = 0; i < numberOfChannels.size(); i++)
	{
		if (_channels.size() == 0)
		{
			Channel newChannel = Channel(clientToInsert, numberOfChannels[i]);
			_channels.push_back(newChannel);
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
					}
				}
				else
				{
					//it goes in an infinite loop
					_channels.push_back(Channel(clientToInsert, numberOfChannels[i]));
					//the break is not the solution
					// break;
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
	for (size_t i = 0; i < _channels.size(); i++)
	{
		std::cout<<"let's go gambling"<<std::endl;
		_channels[i].printClients();
	}

	std::cout<<"Does it come here?"<<std::endl;
}
