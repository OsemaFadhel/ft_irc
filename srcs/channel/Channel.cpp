/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:13:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/09/23 12:02:56 by lnicoter         ###   ########.fr       */
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
	//setting the first user as an operator
	if (_usrData.size() == 0)
		_usrData.push_back(std::make_pair(firstClient, 1));
	else
		_usrData.push_back(std::make_pair(firstClient, 0));

	if (_name.size() > 0)
	{

		for (size_t i = 0; i < charCheck.size(); i++)
		{
			if (_name[0] == charCheck[i])
				break ;
		}
		std::string errMess = constructMessage(ERR_BADCHANMASK, _name);
		send(_usrData[0].first.getFd(), errMess.c_str(), errMess.size(), 0);
	}
	else
	{
		std::string errMess = constructMessage(ERR_NEEDMOREPARAMS, "JOIN");
		send(_usrData[0].first.getFd(), errMess.c_str(), errMess.size(), 0);
	}
	if (_name.find(badCharCheck[0], 0) || _name.find(badCharCheck[1], 0) || _name.find(badCharCheck[2], 0))
	{
		//check for the name of the channel
		std::string errMess = constructMessage(ERR_BADCHANMASK, _name);
		send(_usrData[0].first.getFd(), errMess.c_str(), errMess.size(), 0);
	}
	_name = _name;
	_topic = "";
	_mode = "";
	_password = "";
}


Channel::~Channel()
{}

//The copy constr must do a deep copy of the vector with pairs
//cp constructor implementation

Channel::Channel(const Channel& obj)
{
	if (this == &obj)
		return ;
	_name = obj._name;
	_topic = obj._topic;
	_mode = obj._mode;
	_password = obj._password;
	_limit = obj._limit;
	_usrData = obj._usrData;
}

Channel&		Channel::operator=(const Channel& obj)
{
	if (this == &obj)
		return *this;
	_name = obj._name;
	_topic = obj._topic;
	_mode = obj._mode;
	_password = obj._password;
	_limit = obj._limit;
	_usrData = obj._usrData;
	return *this;
}


std::string	Channel::getName() const
{
	return _name;
}

std::string	Channel::getTopic() const
{
	return _topic;
}

std::string	Channel::getMode() const
{
	return _mode;
}


std::string	Channel::getPassword() const
{
	return _password;
}

int	Channel::getLimit() const
{
	return _limit;
}

std::vector< std::pair< Client, int> >	Channel::getUsrData() const
{
	return _usrData;
}


void	Channel::printClients()
{
	std::vector< std::pair< Client, int > >::iterator	begin;
	std::vector< std::pair< Client, int > >::iterator	end = _usrData.end();

	for (begin = _usrData.begin(); begin != end; ++begin)
	{
		std::cout<<"Read value in the channel "<<_name<<" "<<begin->first<<std::endl;
	}
}


void	Channel::setName(const std::string& name)
{
	_name = name;
}

void	Channel::setTopic(const std::string& topic)
{
	_topic = topic;
}

void	Channel::setMode(const std::string& mode)
{
	_mode = mode;
}

void	Channel::setPassword(const std::string& password)
{
	_password = password;
}

void	Channel::setLimit(int limit)
{
	_limit = limit;
}

void	Channel::setUsrData(std::vector< std::pair< Client, int> > usrData)
{
	_usrData = usrData;
}



/* to implement:
		void		join should i save the channel that are passed? how though
		void		kick(Client* client); // kick client
		void		invite(Client* client); // invite client
		void		topic(Client* client, const std::string& topic); // change or view topic
		void		mode(Client* client, const std::string& mode); // change mode
		mode:
		 i: Set/remove Invite-only channel
		 m: Set/remove moderated channel
		 n: Set/remove channel name changes
		 p: Set/remove private channel
		 s: Secret channel
		 t: Set/remove topic set by channel operator only
		 k <key>: Set/remove the channel key (password)
		 l <limit>: Set the user limit to channel

		PRIVMSG

*/
