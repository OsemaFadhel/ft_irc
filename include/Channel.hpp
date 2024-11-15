/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:11:54 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/28 14:19:27 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <map>
#include <string>
#include "Client.hpp"
#include "Server.hpp"

class Client;

class Channel
{
	private:
		//*my idea is to put, the user and if it is an operator
		std::vector< std::pair< Client, int> >	_usrData; //the user and if it is an operator
		//topic, mode, password, limit are only setted by the operator so they will be intialized to empty
		std::string								_name; //setted when the join command is called
		std::string								_topic; //setted by the operator
		std::map< char, bool >					_mode; //setted by the operator
		std::string								_password; //setted by the operator
		int										_limit; //setted by the operator
		int										_whoInvited;
	public:
		Channel();
		Channel(Client firstClient, std::string channelName);
		~Channel();
		//copy constructor
		Channel(const Channel& obj);
		//copy constructor operator
		Channel&								operator=(const Channel& obj);
		//getters and setters
		std::string								getName() const;
		std::string								getTopic() const;
		std::map<char, bool>					getMode() const;
		std::string								getPassword() const;
		int										getLimit() const;
		std::vector< std::pair< Client, int> >	getUsrData() const;
		bool									getModeValue(char mode);
		int										getWhoInvited();
		void									setName(const std::string& name);
		void									setTopic(const std::string& topic);
		void									setMode(const std::map<char, bool> & mode);
		void									setPassword(const std::string& password);
		void									setLimit(int limit);
		void									setUsrData(std::vector< std::pair< Client, int> > usrData);
		void									removeClient(Client& client);
		void									setWhoInvited(int whoInvited);
		Client									getClientByNickname(std::string nickname);
		Client									*getClientByfd(int fd);

		//checks functions
		bool									isOperator(Client client);
		bool									isInviterOp();
		/*mode
		 i: Set/remove Invite-only channel
		 t: Set/remove the restrictions of the TOPIC command to channel operators
		 k: Set/remove the channel key (password)
		 o: Give/take channel operator privilege
		 l: Set/remove the user limit to channel
		*/
		void		iMode(std::string mode, std::string hypotheticalArgs, int clientSocket);
		void		tMode(std::string mode, std::string hypotheticalArgs, int clientSocket);
		void		kMode(std::string mode, std::string hypotheticalArgs, int clientSocket);
		int			checkKey(std::string keyToChekck, Client clientToInsert);
		void		oMode(std::string mode, std::string hypotheticalArgs, int clientSocket);
		void		lMode(std::string mode, std::string hypotheticalArgs, int clientSocket);
		void		broadcastMessage(std::string message, int clientSocket);

		//optional functions for outputs
		void		printClients();
		int			isInChannel(Client client);
		void		addClient(Client client);
		void		channelContentSize();
		int			findUsr(std::string usrNickname);
		// void		printChanValues();
};

#endif

/*
!missing checks:






I think that for now i don't need to do

*Important feature:
	should i free the vecotrs when the the connection is closed?



*Channel operators behaviour development logic 🧠:
	a channel operator borns when is the first one to enter
	a channel with the JOIN command.
	this is the simplest case where you can define a chanop
	!the chanop is identified by @ prefix next to it's nickname
*dridolfo tips 🗣️
	you should have a SERVEROperator too oh shit with a pass and a username
	the operators aren't only created when you create a channel for the first time


*/
