/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:13:55 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/20 18:40:22 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"

//the user and the name of the channel
//   Command: JOIN
//    Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
//                / "0"

/*
Missing checks:
	checks are correct the function in the join file must be
	changed
It seems the channel is not inserted correctly but i'm building it and i'm
sure of it so i should isolate and check better
*/
Channel::Channel(Client firstClient, std::string channelName)
{
	//check name
	//You should empty the data from the attributes
	//that do not appear here
	std::string	charCheck = CHAR_FOR_CHANNEL_FIRST_LETTER;
	std::string	badCharCheck = BAD_CHAR_FOR_CHANNEL;
	int			syntaxFlag = 0;
	//setting the first user as an operator
	if (_usrData.size() == 0)
		_usrData.push_back(std::make_pair(firstClient, 1));
	else
		_usrData.push_back(std::make_pair(firstClient, 0));

	if (channelName.size() > 0)
	{
		for (size_t i = 0; i < charCheck.size(); i++)
		{
			std::cout<<"testing channel name checks!!!! "<<static_cast<int>(channelName[0])<<std::endl;
			if (channelName[0] == charCheck[i])
				syntaxFlag = 1;
			this->_name = channelName;
		}
		if (syntaxFlag == 0)
		{
			this->_name = "";
			std::cout<<"what kind of name am i passing here??? "<<channelName<<std::endl;
			std::string errMess = constructMessage(ERR_BADCHANMASK, channelName.c_str());
			std::cout<<"the message is "<<errMess<<std::endl;
			send(_usrData[0].first.getFd(), errMess.c_str(), errMess.size(), 0);
		}
	}
	else
	{
		this->_name = "";
		std::string errMess = constructMessage(ERR_NEEDMOREPARAMS, "JOIN");
		send(_usrData[0].first.getFd(), errMess.c_str(), errMess.size(), 0);
	}
	if (_name.find_first_of(badCharCheck) != std::string::npos)
	{
		//check for the name of the channel
		this->_name = "";
		std::string errMess = constructMessage(ERR_BADCHANMASK, channelName.c_str());
		send(_usrData[0].first.getFd(), errMess.c_str(), errMess.size(), 0);
	}
	//porco due prossima volta usa this oppure metti un altro nome per la variabile passata
	this->_topic = "";
	this->_password = "";
	this->_mode['i'] = false;
	this->_mode['t'] = false;
	this->_mode['k'] = false;
	this->_mode['l'] = false;
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

std::map<char, bool>	Channel::getMode() const
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

void	Channel::setMode(const std::map<char, bool> & mode)
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

int			Channel::isInChannel(Client client)
{
	for (size_t i = 0; i < _usrData.size(); i++)
	{
		std::cout<<"nickname "<<_usrData[i].first.getNickname()<<std::endl;
		std::cout<<"i number "<<i<<std::endl;
		std::cout<<"size??? "<<_usrData.size()<<std::endl;
		if (_usrData[i].first.getNickname() == client.getNickname())
			return 1;
	}
	return 0;
}


void	Channel::addClient(Client client)
{
	_usrData.push_back(std::make_pair(client, 0));
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
