/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:38:08 by lnicoter          #+#    #+#             */
/*   Updated: 2024/09/24 14:21:19 by lnicoter         ###   ########.fr       */
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

// void	channelParser(std::string &args)

void	Server::Join(std::string args, int	clientSocket, std::vector< Channel > _channels)
{
	Client	clientToInsert = getClient(clientSocket);
	(void) args;
	(void) clientToInsert;
	(void) _channels;
}
