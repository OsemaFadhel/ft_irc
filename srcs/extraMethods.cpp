/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraMethods.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:13:40 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/15 15:55:59 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	Server::valuesCheck(Client clientToInsert)
{
	std::cout<<"Client nickname: "<<clientToInsert.getNickname()<<std::endl;
	std::cout<<"Client fd: "<<clientToInsert.getFd()<<std::endl;
}


void	Server::channelCheck()
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		_channels[i].printClients();
	}
}

void	Server::deleteEmptyChannels()
{
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i].getUsrData().empty())
		{
			this->_channels.erase(this->_channels.begin() + i);
			std::cout<<"the channel was empty so i eliminated it"<<std::endl;
			i--;
		}
	}
}
