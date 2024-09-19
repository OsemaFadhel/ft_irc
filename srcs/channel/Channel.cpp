/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:13:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/19 23:15:21 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"

//the user and the name of the channel
//   Command: JOIN
//    Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
//                / "0"
Channel::Channel(Client firstClient, std::string _name)
{
	//check name
	//You should empty the data from the attributes
	//that do not appear here
	std::string	charCheck = CHAR_FOR_CHANNEL_FIRST_LETTER;
	std::string	badCharCheck = BAD_CHAR_FOR_CHANNEL;

	if (_usrData.size() == 0)
		_usrData.push_back(std::make_pair(firstClient, 1));
	else
		_usrData.push_back(std::make_pair(firstClient, 0));

	if (_name.size() > 0)
	{

		for (int i = 0; i < charCheck.size(); i++)
		{
			if (_name[0] == charCheck[i])
				break ;
		}
		std::string errMess = constructMessage(ERR_BADCHANMASK, _name);
		send(_usrData[0].first.getFd(), errMess.c_str(), errMess.size(), 0);
	}
	else if (_name.find(badCharCheck[0], 0) || _name.find(badCharCheck[1], 0) || _name.find(badCharCheck[2], 0));
	{
		//check for the name of the channel
		std::string errMess = constructMessage(ERR_BADCHANMASK, _name);
		size_t bytesSent = send(_usrData[0].first.getFd(), errMess.c_str(), errMess.size(), 0);
	}
	_name = _name;
	_topic = "";
	_mode = "";
	_password = "";
}


Channel::~Channel()
{
}

//The copy constr must do a deep copy of the vector with pairs
//cp constructor implementation

