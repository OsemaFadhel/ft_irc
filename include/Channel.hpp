/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:11:54 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/13 18:55:28 by lnicoter         ###   ########.fr       */
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
		std::string								_mode; //setted by the operator
		std::string								_password; //setted by the operator
		int										_limit; //setted by the operator
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
		std::string								getMode() const;
		std::string								getPassword() const;
		int										getLimit() const;
		std::vector< std::pair< Client, int> >	getUsrData() const;
		void									setName(const std::string& name);
		void									setTopic(const std::string& topic);
		void									setMode(const std::string& mode);
		void									setPassword(const std::string& password);
		void									setLimit(int limit);
		void									setUsrData(std::vector< std::pair< Client, int> > usrData);
		void									removeClient(Client& client, std::string reason);
		/*something like this. each client has a channel
		so from the client class, we can call the channel class
		since vector: *it.kick(client); somtehing like this
		*/
		//channel commands for channel operators
		void		kick(Client* client); // kick client
		void		invite(Client* client); // invite client
		void		topic(Client* client, const std::string& topic); // change or view topic
		void		mode(Client* client, const std::string& mode); // change mode
		/*mode
		 i: Set/remove Invite-only channel
		 t: Set/remove the restrictions of the TOPIC command to channel operators
		 k: Set/remove the channel key (password)
		 o: Give/take channel operator privilege
		 l: Set/remove the user limit to channel
		*/
		//optional functions for outputs
		void		printClients();
		int			isInChannel(Client client);
		void		addClient(Client client);
};

#endif
