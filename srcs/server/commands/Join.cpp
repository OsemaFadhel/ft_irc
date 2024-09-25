/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:38:08 by lnicoter          #+#    #+#             */
/*   Updated: 2024/09/25 13:00:30 by lnicoter         ###   ########.fr       */
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
	// for (size_t i = 0; i != std::string::npos; i = args.find(","))
	size_t	i = 0;
	//loop for channels
	while (i != std::string::npos)
	{
		size_t pos = args.find_first_of(" ,", i);
		if (pos != std::string::npos)
		{
			std::string temp = args.substr(i, pos - i);
			// numOfChannels.push_back(args.substr(i));
			std::cout << "temp: " << temp << std::endl;

			numOfChannels.push_back(temp);
			i = pos + 1;
		}
		else
		{
			std::string temp = args.substr(i, pos - i);
			// numOfChannels.push_back(args.substr(i, pos - i));
			std::cout << "temp: " << temp << std::endl;
			numOfChannels.push_back(temp);
			break;
		}
	}
	for (size_t i = 0; i < numOfChannels.size(); i++)
		std::cout << "numOfChannels: " << numOfChannels[i] << std::endl;
	return (numOfChannels);
}

void	Server::Join(std::string args, int	clientSocket, std::vector< Channel > _channels)
{
	Client	clientToInsert = getClient(clientSocket);
	std::vector < std::string > numOfChannels;

	numOfChannels = channelParser(args);
	(void)_channels;
}
